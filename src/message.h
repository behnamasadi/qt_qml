#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDebug>
#include <QObject>

class Message : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
  explicit Message(QObject *parent = nullptr);

  void setText(const QString text) {
    if (text != m_text) {
      m_text = text;
      emit textChanged();
    }
  }

  QString text() const { return m_text; }

  Q_INVOKABLE bool postMessage(const QString &msg) {
    qDebug() << "Called the C++ method with" << msg;
    return true;
  }
public slots:
  void refresh() { qDebug() << "Called the C++ slot"; }

signals:

  void textChanged();

private:
  QString m_text;
};

#endif // MESSAGE_H
