#ifndef WORKER_HPP
#define WORKER_HPP

// https://www.youtube.com/watch?v=G06jT3X3H9E

#include <QDebug>
#include <QObject>

#include <QAuthenticator>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Worker : public QObject {
  Q_OBJECT

private:
  QNetworkAccessManager manager;

public:
  explicit Worker(QObject *parnet = nullptr);

signals:

public slots:
  void get(QString location);
  void post();
  void multipartFormData(QJsonDocument json);
  void postJSONRequestsUpload();
  void sendXMLHttpRequest();
  QJsonDocument postJSONRequestsOld();
  void postJSONRequests();
  void postJSONRequestsNotWorking();

private slots:
  void readyRead();
  void authenticationRequired(QNetworkReply *reply,
                              QAuthenticator *authenticator);
  void encrypted(QNetworkReply *reply);
  void finished(QNetworkReply *reply);
  void preSharedKeyAuthenticationRequired(
      QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
  void proxyAuthenticationRequired(const QNetworkProxy &proxy,
                                   QAuthenticator *authenticator);
  void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
};

#endif // WORKER_HPP
