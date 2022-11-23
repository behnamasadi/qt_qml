#include "user.h"
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

/*

connecting signals and slots

1. SIGNAL/ SLOT macros

QObject::connect(const QObject *, SIGNAL(const char *), const QObject *,
SLOT(const char *) ) QSlider *slider=new QSlider (Qt::Horizontal);
QSpinBox *spin=new QSpinBox(); QObject::connect(slider,
SIGNAL(valueChanged(int)), spin, SLOT(steValue(int)) )


2. Function Pointer
Function Object
Lambda functions
Functors
Standalone functions
 */

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  User *currentuser = new User("foo", 10, User::Dev);

  QTimer *timer = new QTimer(&app);
  timer->start(1000);

  QObject::connect(timer, &QTimer::timeout, currentuser, &User::changeRole);

  QQmlContext *context = view.rootContext();
  context->setContextProperty("_currentuser", currentuser);

  view.setSource(QUrl("qrc:/qml/signal_slot.qml"));
  view.show();

  return app.exec();
}
