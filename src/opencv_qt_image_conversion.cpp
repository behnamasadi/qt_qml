#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  QQmlContext *context = view.rootContext();
  // context->setContextProperty("_currentuser", currentuser);

  view.setSource(QUrl("qrc:/qml/signal_slot.qml"));
  view.show();

  return app.exec();
}
