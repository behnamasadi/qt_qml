#include "WorkerThread.hpp"

void WorkerThread::run() {
  //  QTimer *timer = new QTimer();
  //  timer->start(5000);

  for (int i = 0; i < 5; i++) {
    this->sleep(1);
  }
}

void WorkerThread::setValue(QString value) { m_value = value; }

WorkerThread::WorkerThread() {}

WorkerThread::~WorkerThread() {}
