// https://www.weiy.city/2020/08/how-to-write-and-read-json-file-by-qt/
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

struct Book {
  std::string name;
  double price;
  Book(std::string _name, double _price) {
    name = _name;
    price = _price;
  }
};

QJsonObject writeDataToJSONFile() {
  Book obj1("high school mathematics", 12);
  QJsonObject book1;
  book1.insert("name", obj1.name.c_str());
  book1.insert("price", obj1.price);

  Book obj2("advanced high school mathematics", 14);
  QJsonObject book2;
  book2.insert("name", obj2.name.c_str());
  book2.insert("price", obj2.price);

  QJsonObject content;
  content.insert("book1", book1);
  content.insert("book2", book2);
  return content;
}

void writeToLocalJSONFile(QJsonObject content) {
  QJsonDocument document;

  document.setObject(content);
  QByteArray bytes = document.toJson(QJsonDocument::Indented);
  QString path = "tmp.json";
  QFile file(path);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
    QTextStream iStream(&file);
    iStream.setCodec("utf-8");
    iStream << bytes;
    file.close();
  } else {
    qDebug() << "file open failed: " << path;
  }
}

void readJSONFile(QString path = "tmp.json") {
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
      qDebug() << "fromJson failed: " << jsonError.errorString();
      return;
    }

    if (document.isObject()) {
      QJsonObject jsonObj = document.object();
      for (auto it : jsonObj) {
        // "it" is of type json::reference and has no key() member
        std::cout << "value: " << it.toString().toStdString() << '\n';
      }

      for (auto key : jsonObj.keys()) {
        // "it" is of type json::reference and has no key() member
        // std::cout << "value: " << key. << '\n';
      }

      QStringList books;
      books << "book1"
            << "book2";
      for (auto book : books) {
        if (jsonObj.contains(book)) {
          QJsonObject obj = jsonObj.value(book).toObject();
          QStringList keys = obj.keys();
          for (auto key : keys) {
            auto value = obj.take(key);
            if (value.isDouble()) {
              qDebug() << key << " : " << value.toDouble();
            } else if (value.isString()) {
              qDebug() << key << " : " << value.toString();
            }
          }
        }
      }

      //...
    }
  }
}

int creatQJSON() {
  // Create a JSON object
  QJsonObject jsonObj;
  jsonObj["name"] = "John Doe";
  jsonObj["age"] = 30;
  jsonObj["isMarried"] = false;

  // Create a JSON array and add it to the object
  QJsonArray jsonArr;
  jsonArr.append("Alice");
  jsonArr.append("Bob");
  jsonObj["children"] = jsonArr;

  // Convert the JSON object to a document
  QJsonDocument jsonDoc(jsonObj);

  // Serialize the document to a JSON string
  QString jsonString = jsonDoc.toJson();
  std::cout << jsonString.toStdString() << std::endl;

  // Parse a JSON string to a document
  QJsonParseError parseError;
  QJsonDocument doc2 =
      QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

  // Check for errors during parsing
  if (parseError.error != QJsonParseError::NoError) {
    std::cerr << "Error parsing JSON: "
              << parseError.errorString().toStdString() << std::endl;
    return -1;
  }

  // Extract data from the parsed document
  QJsonObject obj = doc2.object();
  if (obj.contains("name") && obj["name"].isString()) {
    std::cout << "Name: " << obj["name"].toString().toStdString() << std::endl;
  }

  qDebug() << "Iterating over a QJsonObject";

  for (auto it = obj.begin(); it != obj.end(); ++it) {
    QString key = it.key();
    QJsonValue value = it.value();

    // Process key and value
    qDebug() << "Key:" << key << ", Value:" << value;
  }

  return 0;
}

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);

  QJsonObject content = writeDataToJSONFile();
  writeToLocalJSONFile(content);

  // readJSONFile();

  QString path = "response.json";
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray bytes = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

    QJsonObject jsonObj = document.object();
    //    for (auto it : jsonObj) {
    //      // "it" is of type json::reference and has no key() member
    //      std::cout << "value: " << it.toString().toStdString() << '\n';
    //    }

    auto fields = jsonObj["fields"].toObject();
    qDebug() << "url: " << jsonObj["url"].toString();

    foreach (const QString &key, fields.keys()) {
      QJsonValue value = fields.value(key);
      qDebug() << "Key = " << key << ", Value = " << value.toString() << "\n";
    }
  }

  creatQJSON();

  return app.exec();
}
