#include <QGuiApplication>
#include <QProgressDialog>
#include <QQmlContext>
#include <QQuickView>
#include <QTimer>

// https://www.youtube.com/watch?v=dDvf_GDl-8o
// https://stackoverflow.com/questions/28015050/how-to-use-a-qprogressbar
// https://www.ics.com/blog/creating-qml-controls-scratch-progressbar
// https://stackoverflow.com/questions/73524872/how-to-create-a-progress-bar-in-qml-with-slant-lines
// https://www.bogotobogo.com/Qt/Qt5_QProgressDialog_Modal_Modeless_QTimer.php
// https://www.bogotobogo.com/Qt/Qt5_QtConcurrent_QFutureWatcher_QProgressDialog_map.php
int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  // User *currentuser = new User("foo", 10, User::Dev);

  QTimer *timer = new QTimer(&app);
  timer->start(1000);

  // QObject::connect(timer, &QTimer::timeout, currentuser, &User::changeRole);

  QQmlContext *context = view.rootContext();
  // context->setContextProperty("_currentuser", currentuser);

  view.setSource(QUrl("qrc:/qml/signal_slot.qml"));
  view.show();

  int numFiles = 5;

  QProgressDialog progress("Copying files...", "Abort Copy", 0, numFiles);
  progress.setWindowModality(Qt::WindowModal);

  for (int i = 0; i < numFiles; i++) {
    progress.setValue(i);

    if (progress.wasCanceled())
      break;
    //... copy one file
  }
  progress.setValue(numFiles);

  return app.exec();
}
