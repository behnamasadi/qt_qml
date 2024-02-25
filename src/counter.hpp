#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <iostream>

#include <QObject>

class Counter : public QObject {
  /*
  All classes that contain signals or slots must mention Q_OBJECT at the top of
  their declaration. They must also derive (directly or indirectly) from
  QObject.
  */

  Q_OBJECT
public:
  Counter() { m_value = 0; }

  int value() const { return m_value; }
  void setValue(int value);

public slots:
  void valueNotification();

signals:
  void valueChanged(int newValue);

private:
  int m_value;
};

#endif // COUNTER_HPP
