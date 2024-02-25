#include "worker.hpp"
#include <QGuiApplication>
#include <QNetworkAccessManager>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// QHttpMultiPart to QByteArray
// https://stackoverflow.com/questions/33735745/qhttpmultipart-to-qbytearray

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);

  Worker worker;

  worker.post();
  // worker.postJSONRequests();

  return app.exec();
}
