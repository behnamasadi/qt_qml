#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QQuickView view;
  view.setSource(QUrl("qrc:/qml/component_loader.qml"));
  // view.show();

  return app.exec();
}
