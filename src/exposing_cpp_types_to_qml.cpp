#include "message.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <thread>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  Message msg;
  msg.setText("foo");
  QQuickView view;
  view.engine()->rootContext()->setContextProperty("msg", &msg);
  view.setSource(QUrl("qrc:/qml/message.qml"));
  view.show();
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  msg.setText("bar");
  return app.exec();
}
