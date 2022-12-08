#include "PingProcess.h"
#include <QDebug>

Q_LOGGING_CATEGORY(PINGER, "PINGER");

PingProcess::PingProcess(QObject *parent) : QObject{parent} {

  connect(&m_process, &QProcess::errorOccurred, this,
          &PingProcess::errorOccurred);

  connect(&m_process, &QProcess::readyReadStandardError, this,
          &PingProcess::readyReadStandardError);

  connect(&m_process, &QProcess::readyReadStandardOutput, this,
          &PingProcess::readyReadStandardOutput);

  connect(&m_process, &QProcess::started, this, &PingProcess::started);

  connect(&m_process, &QProcess::stateChanged, this,
          &PingProcess::stateChanged);

  connect(&m_process, &QProcess::readyRead, this, &PingProcess::readyRead);

  // finish is overloaded
  connect(&m_process,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          &PingProcess::finished);
  m_address = "";

  qCDebug(PINGER) << "ctor";
}

QString PingProcess::operatingSystem() { return QSysInfo::prettyProductName(); }

QString PingProcess::getAddress() const { return m_address; }

void PingProcess::setAddress(const QString &address) { m_address = address; }

void PingProcess::start() {
  qCInfo(PINGER) << Q_FUNC_INFO;

  m_process.setProgram("ping.exe");
  m_process.setArguments({m_address});
  m_process.start();
}

void PingProcess::stop() {
  qCInfo(PINGER) << Q_FUNC_INFO;
  m_process.close();
}

void PingProcess::errorOccurred(QProcess::ProcessError error) {
  if (QProcess::ProcessState::NotRunning == m_process.state())
    return;
  qCInfo(PINGER) << Q_FUNC_INFO << error;
  emit output("Error");
}

void PingProcess::finished(int exitCode, QProcess::ExitStatus exitStatus) {
  if (QProcess::ProcessState::NotRunning == m_process.state())
    return;
  qCInfo(PINGER) << Q_FUNC_INFO;

  qCInfo(PINGER) << exitCode;
  qCInfo(PINGER) << exitStatus;

  Q_UNUSED(exitCode);
  Q_UNUSED(exitStatus);

  //  emit output(QString::number(exitCode));
  //  emit output(QString::number(exitStatus));

  emit output("complete");
}

void PingProcess::readyReadStandardError() {
  if (QProcess::ProcessState::NotRunning == m_process.state())
    return;
  qCInfo(PINGER) << Q_FUNC_INFO;
  QByteArray data = m_process.readAllStandardError();
  QString message = "Standard Error";
  message.append(m_process.readAllStandardError());
  emit output(message);
}

void PingProcess::readyReadStandardOutput() {

  if (QProcess::ProcessState::NotRunning == m_process.state())
    return;
  qCInfo(PINGER) << Q_FUNC_INFO;
  QByteArray data = m_process.readAllStandardOutput();

  emit output(data.trimmed());
}

void PingProcess::started() { qCInfo(PINGER) << Q_FUNC_INFO; }

void PingProcess::stateChanged(QProcess::ProcessState newState) {
  qCInfo(PINGER) << Q_FUNC_INFO;
  switch (newState) {
  case QProcess::NotRunning:
    emit output("not running");
    break;
  case QProcess::Starting:
    emit output("Starting");
    break;
  case QProcess::Running:
    emit output("Running");
    break;
  }
}

void PingProcess::readyRead() {
  if (QProcess::ProcessState::NotRunning == m_process.state())
    return;
  qCInfo(PINGER) << Q_FUNC_INFO;
  QByteArray data = m_process.readAll().trimmed();
  qCInfo(PINGER) << data;
  emit output(data);
}
