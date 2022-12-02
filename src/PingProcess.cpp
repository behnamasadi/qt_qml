#include "PingProcess.h"
#include <QDebug>

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

  // connect(&m_process, &QProcess::readyRead, this, &PingProcess::readyRead);

  // finish is overloaded
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
  // m_process.start(getCommandPromptName());

  m_process.setProgram("updater");
  m_process.setArguments({m_address});
  m_process.start();
}

void PingProcess::stop() {
  qInfo() << Q_FUNC_INFO;
  m_listening = false;
  m_process.close();
}

void PingProcess::errorOccurred(QProcess::ProcessError error) {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO << error;
  emit output("Error");
}

void PingProcess::finished(int exitCode, QProcess::ExitStatus exitStatus) {
  if (!m_listening)
    return;
  qInfo() << Q_FUNC_INFO;

  qInfo() << exitCode;
  qInfo() << exitStatus;

  Q_UNUSED(exitCode);
  Q_UNUSED(exitStatus);

  //  emit output(QString::number(exitCode));

  //  emit output(QString::number(exitStatus));

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
  QByteArray data = m_process.readAllStandardOutput();

  emit output(data.trimmed());
}

void PingProcess::started() { qInfo() << Q_FUNC_INFO; }

void PingProcess::stateChanged(QProcess::ProcessState newState) {
  qInfo() << Q_FUNC_INFO;
  switch (newState) {
  case QProcess::NotRunning:
    emit output("not running");
    break;
  case QProcess::Starting:
    emit output("Starting");
    break;
  case QProcess::Running:
    emit output("Running");
    // startPing();
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

// QString PingProcess::getCommandPromptName() {
//   qInfo() << Q_FUNC_INFO;

//  if (QSysInfo::productType() == "window") {
//    return "cmd";
//  }

//  else if (QSysInfo::productType() == "osx") {
//    return "/bin/zsh";
//  } else {
//    return "bash";
//  }
//}

// void PingProcess::startPing() {

//  QByteArray command;
//  command.append("ping " + m_address);
//  if (QSysInfo::productType() == "window") {
//    command.append("\n");
//    m_process.write(command);
//  }
//}
