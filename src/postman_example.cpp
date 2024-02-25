#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

#include <QDebug>
#include <QObject>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QAuthenticator>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtGlobal>

void printFromattedReply(QNetworkReply *reply) {

  qDebug()
      << " ********************** reply finished *************************** ";

  if (reply->error() == QNetworkReply::NoError) {
    qDebug() << "=================== Success ===================";
  } else {
    // failure
    qDebug() << "Failure" << reply->errorString();
  }

  qDebug() << "raw reply header: ";
  for (auto &i : reply->rawHeaderPairs())
    qDebug() << i.first << "=" << i.second;

  qDebug() << "requested url: \n" << reply->request().url();

  qDebug() << "raw request header: ";
  for (auto &i : reply->request().rawHeaderList())
    qDebug() << i << "=" << reply->request().rawHeader(i);

  qDebug() << "Entire reply: ";
  QString jsonString(reply->readAll());

  QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
  QString formattedJsonString = doc.toJson(QJsonDocument::Indented);

  qDebug() << formattedJsonString.toStdString().c_str();
}

void printFromattedErrorOccurred(QNetworkReply *reply) {
  qDebug()
      << " ********************** error occurred *************************** ";

  qDebug() << reply->error();
  qDebug() << reply->errorString();

  qDebug() << "raw Header List: " << reply->rawHeaderList();

  qDebug() << "raw Header pair: ";
  for (auto &i : reply->rawHeaderPairs())
    qDebug() << i.first << "," << i.second;

  qDebug() << reply->error();

  qDebug() << reply->request().url();

  qDebug() << reply->readAll();
}

// Whenever more data is received from the network and processed, the
// readyRead() signal is emitted.
void readyRead(QNetworkReply *reply) {
  qDebug() << " ********************** readyRead *************************** ";
}

void multipart() {
  QEventLoop loop;

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  QString path = "modified.json";
  QString uploadurl;

  QFile jsonFile(path);
  if (jsonFile.open(QIODevice::ReadOnly)) {
    QByteArray bytes = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

    QJsonObject jsonObj = document.object();

    auto fields = jsonObj["fields"].toObject();

    uploadurl = jsonObj["url"].toString();

    foreach (const QString &key, fields.keys()) {
      QJsonValue value = fields.value(key);
      QHttpPart textPart;
      QString tmp =
          QString("form-data; name=") + QString("\"") + key + QString("\"");

      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         tmp.toStdString().c_str());
      textPart.setBody(value.toString().toStdString().c_str());
      multiPart->append(textPart);
    }
  }

  QHttpPart imagePart;

  imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("file/zip"));
  imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                      QVariant("form-data; name=\"file\""));

  QFile *file = new QFile("image.jpg");
  file->open(QIODevice::ReadOnly);
  imagePart.setBodyDevice(file);
  file->setParent(multiPart); // we cannot delete the file now, so delete it
                              // with the multiPart

  multiPart->append(imagePart);

  //  const QUrl url(uploadurl);
  QUrl url("https://postman-echo.com/post");

  QNetworkRequest request(url);

  QNetworkAccessManager manager;
  QNetworkReply *reply = manager.post(request, multiPart);
  multiPart->setParent(reply); // delete the multiPart with the reply

  QObject::connect(reply, &QNetworkReply::readyRead,
                   std::bind(&readyRead, reply));

  QObject::connect(reply, &QNetworkReply::finished,
                   std::bind(&printFromattedReply, reply));

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

  QObject::connect(reply, &QNetworkReply::errorOccurred,
                   std::bind(&printFromattedErrorOccurred, reply));
#endif
  loop.exec();
}

void post() {
  QEventLoop loop;
  QNetworkAccessManager manager;

  QObject::connect(&manager, &QNetworkAccessManager::finished, &loop,
                   &QEventLoop::quit);

  QByteArray data;
  data.append("foo1=bar1");
  data.append("&");
  data.append("foo2=bar2");

  QString location = "https://postman-echo.com/post";
  QNetworkRequest request = QNetworkRequest(QUrl(location));

  request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

  QNetworkReply *reply = manager.post(request, data);

  QObject::connect(reply, &QNetworkReply::readyRead,
                   std::bind(&readyRead, reply));

  QObject::connect(reply, &QNetworkReply::finished,
                   std::bind(&printFromattedReply, reply));

  QObject::connect(reply, &QNetworkReply::finished,
                   [=]() { reply->deleteLater(); });

  loop.exec(); // blocks stack until "finished()" has been called
}

void get() {
  QEventLoop loop;
  QNetworkAccessManager manager;

  QString location = "https://postman-echo.com/get?foo1=bar1&foo2=bar2";
  QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(location)));

  QObject::connect(reply, &QNetworkReply::readyRead,
                   std::bind(&readyRead, reply));

  QObject::connect(reply, &QNetworkReply::finished,
                   std::bind(&printFromattedReply, reply));

  loop.exec();
}

void completeExample(int argc, char **argv) {

  QCoreApplication a(argc, argv);

  QTimer timer;
  QNetworkAccessManager *manager = new QNetworkAccessManager();

  QNetworkRequest request;
  timer.start(30000);
  timer.setSingleShot(true);

  request.setUrl(QUrl("http://qt-project.org"));
  request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

  QNetworkReply *rep = manager->post(request, "");
  QObject::connect(&timer, &QTimer::timeout, &a, [&rep]() { rep->abort(); });

  QObject::connect(
      manager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply) {
        qDebug() << "Here!";

        if (reply->error()) {
          qDebug() << "ERROR!";
          qDebug() << reply->errorString();
        } else {

          qDebug()
              << reply->header(QNetworkRequest::ContentTypeHeader).toString();
          qDebug() << reply->header(QNetworkRequest::LastModifiedHeader)
                          .toDateTime()
                          .toString();
          qDebug() << reply->header(QNetworkRequest::ContentLengthHeader)
                          .toULongLong();
          qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                          .toInt();
          qDebug() << reply
                          ->attribute(
                              QNetworkRequest::HttpReasonPhraseAttribute)
                          .toString();
          QFile f("index.html");

          auto data = reply->readAll();
          qDebug() << data;
          if (f.open(QIODevice::WriteOnly)) {
            f.write(data);
          } else {
            qDebug() << "error can not open file";
            qDebug() << reply->readAll();
          }
        }
      });

  QObject::connect(manager, &QNetworkAccessManager::finished, manager,
                   &QNetworkAccessManager::deleteLater);
  QObject::connect(manager, &QNetworkAccessManager::finished, rep,
                   &QNetworkReply::deleteLater);

  a.exec();
}

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  post();
  // get();
  // multipart();
  return app.exec();

  //  completeExample(argc, argv);
}
