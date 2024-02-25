#include "WorkerThread.hpp"
#include <QGuiApplication>
#include <QProgressDialog>
#include <QQmlContext>
#include <QQuickView>

/*
QThreads begin executing in run(), run() starts the event loop by calling exec()
and runs a Qt event loop inside the thread. */

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;

  WorkerThread *thread = new WorkerThread();
  thread->setObjectName("WorkerThreadProcessing");

  thread->setValue("foo");
  thread->start();

  QObject::connect(thread, &QThread::finished,
                   []() { qDebug() << "task in the BG thread finished"; });

  return app.exec();
}
