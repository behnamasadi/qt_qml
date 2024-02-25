#pragma once

#include <QMessageBox>
#include <QObject>
#include <QProgressDialog>
#include <QSettings>

class Project : public QObject {
  Q_OBJECT

  // Q_PROPERTY(fbx::FlightListModel *flightListModel READ flightListModel
  // NOTIFY flightListModelChanged)

public:
  Project(QObject *parent = nullptr);

  // Read & Write project datas
  [[nodiscard]] static Project *fromJson(const QJsonObject &json);
  [[nodiscard]] QJsonObject intoJson();

  ///
  /// GETTERS
  ///

  // bool needsSaving() const;

  // Project informations
  const QString &name() const;

  ///
  /// SETTERS
  ///

  // void setName(const QString &);

  ///
  /// Q INVOKABLES
  ///

  // Q_INVOKABLE void qExportPDF();

signals:
  // void filenameChanged();

public slots:
  // void onProgressUpdated(int p, QString messsage);

private:
  QStringList m_locationsL;
};
