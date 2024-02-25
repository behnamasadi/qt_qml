#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:/qml/slider.qml"));
  QObject *topLevel = engine.rootObjects().value(0);
  QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
  window->show();
  return app.exec();
}
