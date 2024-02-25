#include <QDateTime>
#include <QObject>
#include <QtQml/qqml.h>

class MyMessageType : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
  Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate
                 NOTIFY creationDateChanged)

public:
  QString text();
  void setText(QString text);

  QDateTime creationDate();
  void setCreationDate(QDateTime creationDate);

signals:
  void textChanged();
  void creationDateChanged();

private:
  QString m_text;
  QDateTime m_creationDate;
};
