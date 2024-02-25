#include "user.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  User *currentuser = new User("foo", 10, User::Dev);
  QQmlContext *context = view.rootContext();
  context->setContextProperty("_currentuser", currentuser);
  view.setSource(QUrl("qrc:/qml/signal_slot.qml"));
  view.show();

  QTimer *timer = new QTimer(&app);
  timer->start(1000);

  QObject::connect(timer, &QTimer::timeout, currentuser, &User::changeRole);
  return app.exec();
}
