#include "user.h"

#include <QGuiApplication>
#include <QObject>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;
  QQmlContext *context = view.rootContext();

  // the under line is just a convention to emphasis it is coming from cpp in
  // the qml file
  context->setContextProperty("_aString", QString("AAAA"));
  context->setContextProperty("_aSize", QSize(400, 600));

  User *currentuser = new User("foo", 10, User::Dev);
  context->setContextProperty("_currentuser", currentuser);

  view.setSource(QUrl("qrc:/qml/context_property.qml"));
  view.show();

  return app.exec();
}
