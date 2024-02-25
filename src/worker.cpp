
#include "worker.hpp"
#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Worker::Worker(QObject *parnet) : QObject(parnet) {

  QObject::connect(&manager, &QNetworkAccessManager::authenticationRequired,
                   this, &Worker::authenticationRequired);

  QObject::connect(&manager, &QNetworkAccessManager::encrypted, this,
                   &Worker::encrypted);

  //  QObject::connect(&manager,
  //                   &QNetworkAccessManager::preSharedKeyAuthenticationRequired,
  //                   this, &Worker::authenticationRequired);

  QObject::connect(&manager, &QNetworkAccessManager::sslErrors, this,
                   &Worker::sslErrors);

  QObject::connect(&manager,
                   &QNetworkAccessManager::proxyAuthenticationRequired, this,
                   &Worker::proxyAuthenticationRequired);
}

void Worker::get(QString location) {
  qInfo() << "Getting from server...";
  QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(location)));
  QObject::connect(reply, &QNetworkReply::readyRead, this, &Worker::readyRead);
}

void Worker::post() {

  /*

  curl -i -H "Content-Type: application/json" -d '{"key1": "value1", "key2":
  "value2"}' -X POST http://myserver.com/api


  QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
  const QUrl url(QStringLiteral("http://myserver.com/api"));
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

      QJsonObject obj;
      obj["key1"] = "value1";
      obj["key2"] = "value2";
      QJsonDocument doc(obj);
      QByteArray data = doc.toJson();
      // or
      // QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}");
      QNetworkReply *reply = mgr->post(request, data);


  */
  QEventLoop loop;
  qInfo() << "Posting to server...";

  QString location = "https://explorev1.dev.foo.cloud/api/store/log";

  //'https://explorev1.dev.foo.cloud/api/store/log' \
//-H 'accept: application/json' \
//-H 'x-fbx-uuid: 12345678901234567000' \
//-H 'Authorization: Bearer xxxxxxxxxxxxxxxxxxxxxxxxxxx\
//-H 'Content-Type: application/json' \
//-d '{
  //"filename": "00000-2010-10-20_20-10-00.log",
  //"hash": "a2dee47ba6268925da97750ab742baf67f02e2fb54ce23d499fb66a5b0222903",
  //"size": 123456789,
  //"timestamp": 1674234109

  QNetworkRequest request = QNetworkRequest(QUrl(location));

  // request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
  request.setRawHeader("accept", "application/json");
  request.setRawHeader("x-fbx-uuid", "12345678901234567000");
  request.setRawHeader(
      "Authorization",
      "Bearer "
      "xxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  QJsonObject obj;
  obj["filename"] = "00000-2010-10-20_20-10-00.log";
  obj["hash"] =
      "a2dee47ba6268925da97750ab742baf67f02e2fb54ce23d499fb66a5b0222903";
  obj["size"] = 123456789;
  obj["timestamp"] = 1674234109;

  QJsonDocument doc(obj);
  QByteArray data = doc.toJson();

  QNetworkReply *reply = manager.post(request, data);
  //  QObject::connect(reply, &QNetworkReply::readyRead, this,
  //  &Worker::readyRead);

  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    QEventLoop loop;

    QString jsonString(reply->readAll());

    QJsonDocument document = QJsonDocument::fromJson(jsonString.toUtf8());

    qDebug() << "-----------------------------------------------finished-------"
                "----------------------------------------";

    QHttpMultiPart *multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QString path = "modified.json";
    QString uploadurl;

    QJsonObject jsonObj = document.object();

    auto fields = jsonObj["fields"].toObject();

    uploadurl = jsonObj["url"].toString();

    // no need
    // multiPart->setBoundary("boundary_.oOo._RU42cq4l1RheIT5FOoUWRRSk4DvDBL/r");

    //    qDebug() << "***********************";
    foreach (const QString &key, fields.keys()) {
      QJsonValue value = fields.value(key);
      //       qDebug() << key << "=" << value.toString();

      QHttpPart textPart;

      //      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
      //                         QVariant(QString("form-data; name=") +
      //                         QString("\"") +
      //                                  key + QString("\"")));

      QString tmp =
          QString("form-data; name=") + QString("\"") + key + QString("\"");

      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         tmp.toStdString().c_str());

      qDebug() << tmp.toStdString().c_str();
      qDebug() << value.toString().toStdString().c_str();

      textPart.setBody(value.toString().toStdString().c_str());
      multiPart->append(textPart);
    }

    // qDebug() << "***********************";

    QHttpPart imagePart;

    imagePart.setHeader(QNetworkRequest::ContentTypeHeader,
                        QVariant("file/zip"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"file\""));

    QFile *file = new QFile("image.jpg");
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it
                                // with the multiPart

    multiPart->append(imagePart);

    const QUrl url(uploadurl);

    QNetworkRequest request(url);

    QNetworkAccessManager manager;
    QNetworkReply *replyUpload = manager.post(request, multiPart);
    multiPart->setParent(replyUpload); // delete the multiPart with the reply

    qDebug() << "raw Header List: " << replyUpload->rawHeaderList();

    qDebug() << "raw Header pair: ";
    for (auto &i : replyUpload->rawHeaderPairs())
      qDebug() << i.first << "," << i.second;

    qDebug() << replyUpload->request().url();

    qDebug() << replyUpload->readAll();

    //    qDebug() << "request raw HeaderList:";
    //    qDebug() << reply->request().rawHeaderList();

    for (auto &i : replyUpload->request().rawHeaderList())
      qDebug() << i << "=" << replyUpload->request().rawHeader(i);

    loop.exec();
  });

  loop.exec();
}

void Worker::multipartFormData(QJsonDocument json) {

  // https://doc.qt.io/qt-6/qhttpmultipart.html

  /*
  QHttpMultiPart::MixedType
  QHttpMultiPart::RelatedType
  QHttpMultiPart::FormDataType
  QHttpMultiPart::AlternativeType
  */

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  // 1. text part
  QHttpPart textPart;

  auto fields = json["fields"].toObject();

  qDebug() << fields;
  qDebug() << json;

  //  foreach (const auto &key : fields.keys()) {
  //    qDebug() << key << "=" << fields.value(key);
  //  }

  foreach (const QString &key, fields.keys()) {
    QJsonValue value = fields.value(key);
    qDebug() << "Key = " << key << ", Value = " << value.toString();
  }

  textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                     QVariant("form-data; name=\"text\""));
  textPart.setBody("my text");

  // 2. image part
  QHttpPart imagePart;
  imagePart.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("image/jpeg"));
  imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                      QVariant("form-data; name=\"image\""));

  QFile *file = new QFile("image.jpg");
  file->open(QIODevice::ReadOnly);
  imagePart.setBodyDevice(file);

  // we cannot delete the file now, so delete it with the multiPart
  file->setParent(multiPart);

  // appending all the parts
  multiPart->append(textPart);
  multiPart->append(imagePart);

  QUrl url("http://my.server.tld");
  QNetworkRequest request(url);

  QNetworkAccessManager manager;
  QNetworkReply *reply = manager.post(request, multiPart);

  // delete the multiPart with the reply
  multiPart->setParent(reply);

  // here connect signals etc.
}

QJsonDocument Worker::postJSONRequestsOld() {
  /*

    For JSON:    Content-Type: application/json
    For JSON-P:  Content-Type: application/javascript
  */

  QNetworkAccessManager *mgr = new QNetworkAccessManager();
  const QUrl url(QStringLiteral(""));
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  request.setRawHeader("Authorization", "Bearer ");
  request.setRawHeader("Accept", "application/json");

  request.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, "IE6");

  QJsonObject obj;
  obj["key1"] = "value1";
  //  obj["key2"] = "value2";
  //  obj.insert("item1", "value1");
  //  obj.insert("item2", "value2");

  QJsonDocument doc(obj);
  QByteArray data = doc.toJson();
  // or
  // QByteArray data("{\"key1\":\"value1\",\"key2\":\"value2\"}");
  QNetworkReply *reply = mgr->post(request, data);

  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() == QNetworkReply::NoError) {
      // QString contents = QString::fromUtf8(reply->readAll());
      QByteArray response_data = reply->readAll();
      QJsonDocument json = QJsonDocument::fromJson(response_data);
      //      qDebug() << json["url"];
      //      qDebug() << json["fields"];

      QHttpMultiPart *multiPart =
          new QHttpMultiPart(QHttpMultiPart::FormDataType);

      // 1. text part

      auto fields = json["fields"].toObject();

      foreach (const QString &key, fields.keys()) {
        QJsonValue value = fields.value(key);
        qDebug() << "Key = " << key << ", Value = " << value.toString();

        QHttpPart textPart;

        textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                           QVariant("form-data; name=\"text\""));

        textPart.setBody(value.toString().toStdString().c_str());
        multiPart->append(textPart);
      }

      QHttpPart zipPart;
      zipPart.setHeader(QNetworkRequest::ContentTypeHeader,
                        QVariant("application/gzip"));

      QFile *file = new QFile("file.zip");
      file->open(QIODevice::ReadOnly);
      zipPart.setBodyDevice(file);

      // we cannot delete the file now, so delete it with the multiPart
      file->setParent(multiPart);

      // appending all the parts

      multiPart->append(zipPart);

      QUrl url(json["url"].toString());
      qDebug() << json["url"];
      QNetworkRequest requestupload(url);

      QNetworkAccessManager managerupload;
      QNetworkReply *replyupload = managerupload.post(requestupload, multiPart);

      // delete the multiPart with the reply
      multiPart->setParent(replyupload);

      QObject::connect(replyupload, &QNetworkReply::finished, [=]() {
        qDebug() << "uploaded";

        qDebug() << replyupload;
      });

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

      QObject::connect(replyupload, &QNetworkReply::errorOccurred, [=]() {
        qDebug() << "errorOccurred";

        qDebug() << replyupload;
      });
#endif

      return json;
    } else {
      QString err = reply->errorString();
      qDebug() << err;
    }
    reply->deleteLater();
  });

  /*
  QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

    QUrl url = QUrl("http://myserver.com/api");

    QJsonObject param;
    param.insert("key1", QJsonValue::fromVariant("value1"));
    param.insert("key2", QJsonValue::fromVariant("value2"));

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
  "application/x-www-form-urlencoded");

    QNetworkReply* reply = mgr->post(request,
  QJsonDocument(param).toJson(QJsonDocument::Compact));


    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    timer.start(10000);   // 10 secs. timeout
    loop.exec();

    if(timer.isActive())
    {
        timer.stop();
        if(reply->error() == QNetworkReply::NoError)
        {
            // Success
            QByteArray buffer = reply->readAll();

            qDebug()<<buffer;
        }
        else
        {
            // handle error
            QString error = reply->errorString();
            qDebug()<< "reply->errorString() " << error;
        }
    }
    else
    {
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        reply->abort();
    }

    reply->deleteLater();

  */
  return QJsonDocument();
}

void Worker::postJSONRequestsNotWorking() {

  QEventLoop loop;

  QString path = "response.json";
  QString uploadurl;

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  // QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::MixedType);

  QFile jsonFile(path);
  if (jsonFile.open(QIODevice::ReadOnly)) {
    QByteArray bytes = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

    QJsonObject jsonObj = document.object();

    auto fields = jsonObj["fields"].toObject();

    uploadurl = jsonObj["url"].toString();

    // no need
    // multiPart->setBoundary("boundary_.oOo._RU42cq4l1RheIT5FOoUWRRSk4DvDBL/r");

    qDebug() << "***********************";
    foreach (const QString &key, fields.keys()) {
      QJsonValue value = fields.value(key);
      // qDebug() << key << "=" << value.toString();

      QHttpPart textPart;

      //      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
      //                         QVariant(QString("form-data; name=") +
      //                         QString("\"") +
      //                                  key + QString("\"")));

      QString tmp =
          QString("form-data; name=") + QString("\"") + key + QString("\"");

      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         tmp.toStdString().c_str());

      qDebug() << tmp.toStdString().c_str();

      qDebug() << value.toString().toStdString().c_str();

      textPart.setBody(value.toString().toStdString().c_str());
      multiPart->append(textPart);
    }

    qDebug() << "***********************";
  }

  QHttpPart zipPart;
  zipPart.setHeader(QNetworkRequest::ContentTypeHeader,
                    QVariant("application/gzip"));

  // form-data; name="file";
  // filename="/C:/Users/basadi/code/qt_qml/build/Debug/response.zip"

  //  zipPart.setHeader(QNetworkRequest::ContentDispositionHeader,
  //                    QVariant("form-data; name=\"file\"; "
  //                             "filename=\"/C:/Users/basadi/code/qt_qml/build/"
  //                             "Debug/response.zip\""));

  zipPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                    QVariant("form-data; name=\"file\"; "
                             "filename=response.zip\""));

  QFile *file = new QFile("response.zip");
  file->open(QIODevice::ReadOnly);
  zipPart.setBodyDevice(file);

  // we cannot delete the file now, so delete it with the multiPart
  file->setParent(multiPart);

  // appending all the parts

  multiPart->append(zipPart);

  // multiPart->dumpObjectInfo();

  QNetworkAccessManager *mgr = new QNetworkAccessManager();

  // const QUrl url(uploadurl);
  const QUrl url("https://postman-echo.com/post");
  QNetworkRequest *request = new QNetworkRequest(QUrl(url));

  qDebug() << "request rawHeaderList()";
  for (auto &i : request->rawHeaderList())
    qDebug() << i;

  qDebug() << "-----------------";

  /*
   *  The boundary of the QHttpMultiPart is constructed with the string
   * "boundary_.oOo._" followed by random characters, and provides enough
   * uniqueness to make sure it does not occur inside the parts itself. If
   * desired, the boundary can still be set via setBoundary().
   */
  qDebug() << "boundary: " << multiPart->boundary();

  qDebug() << "multiPart->children():";

  for (auto &i : multiPart->children()) {
    qDebug() << i;
    qDebug() << i->objectName();
  }

  qDebug() << "-----------------";

  qDebug() << multiPart->dynamicPropertyNames();

  // multiPart ->findChild()

  request->setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
  QNetworkReply *reply = mgr->post(*request, multiPart);

  // delete the multiPart with the reply
  multiPart->setParent(reply);

  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    //    qDebug() << "finished";

    //    qDebug() << reply;

    //    qDebug() << reply->error();
    //    qDebug() << reply->errorString();

    //    // qDebug() << reply->header()
    //    qDebug() << reply->rawHeaderList();
  });

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

  QObject::connect(reply, &QNetworkReply::errorOccurred, [=]() {
    //    qDebug() << "errorOccurred";
    //    qDebug() << reply->error();
    //    qDebug() << reply->errorString();
    //    qDebug() << reply;
    qDebug() << "raw Header List: " << reply->rawHeaderList();

    qDebug() << "raw Header pair: ";
    for (auto &i : reply->rawHeaderPairs())
      qDebug() << i.first << "," << i.second;

    qDebug() << reply->error();

    qDebug() << reply->request().url();

    qDebug() << reply->readAll();

    qDebug() << "request raw HeaderList:";
    qDebug() << reply->request().rawHeaderList();

    for (auto &i : reply->request().rawHeaderList())
      qDebug() << i << "=" << reply->request().rawHeader(i);

    // qDebug() << reply->request().;

    //    typedef QPair<QByteArray, QByteArray> RawHeaderPair;
    //    const QList<RawHeaderPair>
  });
#endif
  loop.exec();
}

void Worker::postJSONRequests() {
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

    // no need
    // multiPart->setBoundary("boundary_.oOo._RU42cq4l1RheIT5FOoUWRRSk4DvDBL/r");

    //    qDebug() << "***********************";
    foreach (const QString &key, fields.keys()) {
      QJsonValue value = fields.value(key);
      // qDebug() << key << "=" << value.toString();

      QHttpPart textPart;

      //      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
      //                         QVariant(QString("form-data; name=") +
      //                         QString("\"") +
      //                                  key + QString("\"")));

      QString tmp =
          QString("form-data; name=") + QString("\"") + key + QString("\"");

      textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                         tmp.toStdString().c_str());

      //      qDebug() << tmp.toStdString().c_str();
      //      qDebug() << value.toString().toStdString().c_str();

      textPart.setBody(value.toString().toStdString().c_str());
      multiPart->append(textPart);
    }

    // qDebug() << "***********************";
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

  const QUrl url(uploadurl);
  //  QUrl url("https://postman-echo.com/post");

  QNetworkRequest request(url);

  QNetworkAccessManager manager;
  QNetworkReply *reply = manager.post(request, multiPart);
  multiPart->setParent(reply); // delete the multiPart with the reply

  QObject::connect(reply, &QNetworkReply::finished, [=]() {
    qDebug() << "-----------------------------------------------finished-------"
                "----------------------------------------";
    //    //    qDebug() << reply->error();
    //    //    qDebug() << reply->errorString();
    //    //    qDebug() << reply;
    qDebug() << "raw Header List: " << reply->rawHeaderList();

    qDebug() << "raw Header pair: ";
    for (auto &i : reply->rawHeaderPairs())
      qDebug() << i.first << "," << i.second;

    qDebug() << reply->request().url();

    qDebug() << reply->readAll();

    //    qDebug() << "request raw HeaderList:";
    //    qDebug() << reply->request().rawHeaderList();

    for (auto &i : reply->request().rawHeaderList())
      qDebug() << i << "=" << reply->request().rawHeader(i);
  });
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

  QObject::connect(reply, &QNetworkReply::errorOccurred, [=]() {
    qDebug() << "**********************************************errorOccurred***"
                "*******************************************";
    //      //    qDebug() << reply->error();
    //      //    qDebug() << reply->errorString();
    //      //    qDebug() << reply;
    //      qDebug() << "raw Header List: " << reply->rawHeaderList();

    //      qDebug() << "raw Header pair: ";
    //      for (auto &i : reply->rawHeaderPairs())
    //          qDebug() << i.first << "," << i.second;

    //      qDebug() << reply->error();

    //      qDebug() << reply->request().url();

    qDebug() << reply->readAll();

    //      qDebug() << "request raw HeaderList:";
    //      qDebug() << reply->request().rawHeaderList();

    //      for (auto &i : reply->request().rawHeaderList())
    //          qDebug() << i << "=" << reply->request().rawHeader(i);
  });
#endif

  loop.exec();
}

void Worker::postJSONRequestsUpload() {

  QJsonObject obj;

  QString data; // assume this holds the json string

  data = "";

  QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());

  auto fields = json["fields"].toObject();

  QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

  // 1. text part

  foreach (const QString &key, fields.keys()) {
    QJsonValue value = fields.value(key);
    // qDebug() << "Key = " << key << ", Value = " << value.toString();

    QHttpPart textPart;

    textPart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"text\""));

    textPart.setBody(value.toString().toStdString().c_str());
    multiPart->append(textPart);
  }

  QHttpPart zipPart;
  zipPart.setHeader(QNetworkRequest::ContentTypeHeader,
                    QVariant("application/gzip"));

  QFile *file = new QFile("00063-2023-03-08_10-23-26.log.zip");
  file->open(QIODevice::ReadOnly);
  zipPart.setBodyDevice(file);

  // we cannot delete the file now, so delete it with the multiPart
  file->setParent(multiPart);

  // appending all the parts

  multiPart->append(zipPart);

  QHttpMultiPart *emptymultiPart =
      new QHttpMultiPart(QHttpMultiPart::FormDataType);

  QUrl url(json["url"].toString());
  // qDebug() << json["url"];
  QNetworkRequest requestupload(url);

  QNetworkAccessManager managerupload;
  QNetworkReply *replyupload =
      managerupload.post(requestupload, emptymultiPart);

  // delete the multiPart with the reply
  multiPart->setParent(replyupload);

  QObject::connect(replyupload, &QNetworkReply::finished, [=]() {
    qDebug() << "uploaded";

    qDebug() << replyupload;
  });
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)

  QObject::connect(replyupload, &QNetworkReply::errorOccurred, [=]() {
    qDebug() << "errorOccurred";

    qDebug() << replyupload;
  });
#endif
  QObject::connect(replyupload, &QNetworkReply::readyRead, this,
                   &Worker::readyRead);

  replyupload->deleteLater();
}

/*
QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

QUrl url = QUrl("http://myserver.com/api");

QJsonObject param;
param.insert("key1", QJsonValue::fromVariant("value1"));
param.insert("key2", QJsonValue::fromVariant("value2"));

QNetworkRequest request(url);

request.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");

QNetworkReply* reply = mgr->post(request,
                                 QJsonDocument(param).toJson(QJsonDocument::Compact));


QTimer timer;
timer.setSingleShot(true);

QEventLoop loop;
connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
timer.start(10000);   // 10 secs. timeout
loop.exec();

if(timer.isActive())
{
    timer.stop();
    if(reply->error() == QNetworkReply::NoError)
    {
        // Success
        QByteArray buffer = reply->readAll();

        qDebug()<<buffer;
    }
    else
    {
        // handle error
        QString error = reply->errorString();
        qDebug()<< "reply->errorString() " << error;
    }
}
else
{
    disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    reply->abort();
}

reply->deleteLater();

*/

void Worker::sendXMLHttpRequest() {
  // https://doc.qt.io/qt-6/qtqml-xmlhttprequest-example.html
}

void Worker::authenticationRequired(QNetworkReply *reply,
                                    QAuthenticator *authenticator) {}

void Worker::encrypted(QNetworkReply *reply) {
  Q_UNUSED(reply);
  qInfo() << "encrypted";
}

void Worker::finished(QNetworkReply *reply) {
  qInfo() << "finished";
  Q_UNUSED(reply);
}

void Worker::preSharedKeyAuthenticationRequired(
    QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator) {

  Q_UNUSED(reply);
  Q_UNUSED(authenticator);

  qInfo() << "preSharedKeyAuthenticationRequired";
}

void Worker::proxyAuthenticationRequired(const QNetworkProxy &proxy,
                                         QAuthenticator *authenticator) {
  Q_UNUSED(proxy);
  Q_UNUSED(authenticator);

  qInfo() << "proxyAuthenticationRequired";
}

void Worker::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {

  Q_UNUSED(reply);
  Q_UNUSED(errors);
  qInfo() << "sslErrors";
}

void Worker::readyRead() {

  qInfo() << "Readyread";
  QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
  if (reply)
    qInfo() << reply->readAll();
}
