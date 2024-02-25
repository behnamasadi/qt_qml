#include "mytimer.h"
#include <QColor>
#include <QDebug>

mytimer::mytimer(QObject *parent) : QObject(parent) {
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &mytimer::addOneSecond);
  timer->start(1000);
}

void mytimer::addOneSecond() { qDebug() << QString::fromStdString(("foo")); }
