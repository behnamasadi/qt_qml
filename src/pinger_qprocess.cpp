#include "PingProcess.h"
#include "outputPublisher.hpp"
#include <QApplication>
#include <QGuiApplication>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickWindow>
#include <iostream>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  QQmlContext *context = view.rootContext();

  PingProcess pinger;

  pinger.setAddress("4.2.2.4");

  context->setContextProperty("_OS", pinger.operatingSystem());
  context->setContextProperty("_pinger", &pinger);

  // connect(&pinger, &PingProcess::output, &publisher,
  // &outputPublisher::print);

  //  User *currentuser = new User("foo", 10, User::Dev);
  //  context->setContextProperty("_currentuser", currentuser);

  view.setSource(QUrl("qrc:/qml/pinger.qml"));
  view.show();
  return app.exec();

  //  outputPublisher publisher;
  //  //connect(&pinger, &PingProcess::output, &publisher,
  //  &outputPublisher::print);

  //  return app.exec();

  /*
  QObject *parent;
  QString program = "C:\\Windows\\System32\\PING.EXE";
  QStringList arguments;
  arguments << "-n 10 "
            << "example.com";
  QProcess *myProcess = new QProcess(parent);
  myProcess->start(program, arguments);
*/
}
