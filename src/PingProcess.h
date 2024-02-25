#ifndef PINGPROCESS_H
#define PINGPROCESS_H

#include "qqml.h"
#include <QLoggingCategory>
#include <QObject>
#include <QProcess>

Q_DECLARE_LOGGING_CATEGORY(PINGER)

class PingProcess : public QObject {
  Q_OBJECT
  QML_ELEMENT
public:
  explicit PingProcess(QObject *parent = nullptr);
  QString operatingSystem();
  QString getAddress() const;
  Q_INVOKABLE void setAddress(const QString &address);

signals:
  void output(QString data);

public slots:
  void start();
  void stop();

  /*The following slot are communication with qprocess*/
private slots:
  void errorOccurred(QProcess::ProcessError error);
  void finished(int exitCode, QProcess::ExitStatus exitStatus);
  void readyReadStandardError();
  void readyReadStandardOutput();
  void started();
  void stateChanged(QProcess::ProcessState newState);
  void readyRead();

private:
  QProcess m_process;
  QString m_address;
};

#endif // PINGPROCESS_H
