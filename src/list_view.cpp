#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  QQuickView view;
  // both of them work:
  view.setSource(QUrl("qrc:/qml/list_view.qml"));
  // view.setSource(QUrl::fromLocalFile("qml/simple_quickview.qml"));

  view.show();
  return app.exec();
}
