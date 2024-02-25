#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWindow>
#include <iostream>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  QQmlEngine *engine = new QQmlEngine;
  QQmlComponent component(engine, QUrl("qrc:/qml/simple_quickview.qml"));

  QObject *myObject = component.create();
  QQuickItem *item = qobject_cast<QQuickItem *>(myObject);
  int width = item->width(); // width = 200
  std::cout << width << std::endl;
  //   app.exec();
}
