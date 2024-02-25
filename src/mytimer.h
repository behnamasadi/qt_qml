#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>

class mytimer : public QObject {
  Q_OBJECT
public:
  explicit mytimer(QObject *parent = nullptr);

private slots:
  void addOneSecond();

signals:
  void mySignal(int value); // emit mySignal(value)
};

#endif // MYTIMER_H
