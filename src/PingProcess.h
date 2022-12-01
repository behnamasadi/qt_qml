#ifndef PINGPROCESS_H
#define PINGPROCESS_H

#include <QObject>
#include <QProcess>

class PingProcess : public QObject
{
    Q_OBJECT
public:
    explicit PingProcess(QObject *parent = nullptr);
    QString operatingSystem();
    QString getAddress() const;
    void setAddress(const QString  &address);


signals:
    void output(QString data);

public slots:
    void start();
    void stop();

private slots:
    void errorOccoured(QProcess::ProcessError  error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();
    void stateChanged(QProcess::ProcessState newState);
    void readyRead();

private:
    QProcess m_process;
    QString m_address;
    QString getProcess();
    void startPing();
    bool m_listening;

};

#endif // PINGPROCESS_H
