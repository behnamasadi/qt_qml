#include "PingProcess.h"
#include <QDebug>

PingProcess::PingProcess(QObject *parent) : QObject{parent} {

  //  QObject::connect(&a, &Counter::valueChanged, &b, &Counter::setValue);
  // QObject::connect(scrollBar, SIGNAL(valueChanged(int)),  label,
  // SLOT(setNum(int)));

  connect(&m_process, &QProcess::errorOccurred, this,
          &PingProcess::errorOccoured);

  connect(&m_process, &QProcess::readyReadStandardError, this,
          &PingProcess::readyReadStandardError);

  connect(&m_process, &QProcess::readyReadStandardOutput, this,
          &PingProcess::readyReadStandardOutput);

  connect(&m_process, &QProcess::started, this, &PingProcess::started);

  connect(&m_process, &QProcess::stateChanged, this,
          &PingProcess::stateChanged);

  connect(&m_process, &QProcess::readyRead, this, &PingProcess::readyRead);

  connect(&m_process,
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
          &PingProcess::finished);
  m_listening = false;
  m_address = "";
}

QString PingProcess::operatingSystem() { return QSysInfo::prettyProductName(); }

QString PingProcess::getAddress() const { return m_address; }

void PingProcess::setAddress(const QString &address) { m_address = address; }

void PingProcess::start() {
  qInfo() << Q_FUNC_INFO;
  m_listening = true;
  m_process.start(getProcess());
}

void PingProcess::stop() {
  qInfo() << Q_FUNC_INFO;
  m_listening = false;
  m_process.close();
}

void PingProcess::errorOccoured(QProcess::ProcessError error) {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO << error;
  emit output("Error");
}

void PingProcess::finished(int exitCode, QProcess::ExitStatus exitStatus) {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO;
  Q_UNUSED(exitCode);
  Q_UNUSED(exitStatus);
  emit output("complete");
}

void PingProcess::readyReadStandardError() {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO;
  QByteArray data = m_process.readAllStandardError();
  QString message = "Standard Error";
  message.append(m_process.readAllStandardError());
  emit output(message);
}

void PingProcess::readyReadStandardOutput() {

  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO;
  QByteArray data = m_process.readAllStandardError();

  emit output(data.trimmed());
}

void PingProcess::started() { qInfo() << Q_FUNC_INFO; }

void PingProcess::stateChanged(QProcess::ProcessState newState) {
  qInfo() << Q_FUNC_INFO;
  switch (newState) {
  case QProcess::NotRunning:
    emit("not running");
    break;
  case QProcess::Starting:
    emit("Starting");
    break;
  case QProcess::Running:
    emit("Running");
    startPing();
    break;
  default:
    break;
  }
}

void PingProcess::readyRead() {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO;
  QByteArray data = m_process.readAll().trimmed();
  qInfo() << data;
  emit output(data);
}

QString PingProcess::getProcess() {
  qInfo() << Q_FUNC_INFO;

  if (QSysInfo::productType() == "window") {
    return "cmd";
  }

  else if (QSysInfo::productType() == "osx") {
    return "/bin/zsh";
  } else {
    return "bash";
  }
}

void PingProcess::startPing() {

  QByteArray command;
  command.append("ping" + m_address);
  if (QSysInfo::productType() == "window") {
    command.append("\n");
    m_process.write(command);
  }
}
