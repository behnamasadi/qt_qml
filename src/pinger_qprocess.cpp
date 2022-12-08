#include "PingProcess.h"
#include "outputPublisher.hpp"
#include <QApplication>
#include <QGuiApplication>
#include <QMessageBox>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickWindow>
#include <iostream>

int main(int argc, char **argv) {

  //  QGuiApplication app(argc, argv);
  QApplication app(argc, argv);

  QQuickView view;

  QQmlContext *context = view.rootContext();

  PingProcess pinger;

  // pinger.setAddress("4.2.2.4");

  context->setContextProperty("_OS", pinger.operatingSystem());
  context->setContextProperty("_pinger", &pinger);

  view.setSource(QUrl("qrc:/qml/pinger.qml"));
  view.show();

  QObject::connect(&pinger, &PingProcess::output, [=](QString newValue) {
    QMessageBox msgBox;
    msgBox.setText(newValue);
    msgBox.exec();
  });

  return app.exec();
}
