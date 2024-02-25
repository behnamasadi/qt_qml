#include "database.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  QQmlContext *context = view.rootContext();

  Database db;
  context->setContextProperty("_db", &db);

  view.setSource(QUrl("qrc:/qml/receiving_signals_with_signal_handlers.qml"));
  view.show();

  return app.exec();
}
