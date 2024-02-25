
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStandardPaths>
#include <QStorageInfo>
#include <QString>

#include <QLoggingCategory>
#include <filesystem>

Q_LOGGING_CATEGORY(cat, "cat")

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QStringList locations =
      QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);

  qDebug() << locations << "\n";

  qDebug() << QStandardPaths::standardLocations(QStandardPaths::DataLocation)
           << "\n";

  qDebug() << QStandardPaths::writableLocation(
      QStandardPaths::PicturesLocation);
  qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

  // can also set QT_LOGGING_RULES to cat=false to turn of the message
  // https://stackoverflow.com/questions/62678216/why-would-i-prefer-qcdebug-over-qdebug
  qCDebug(cat) << "Hello World!";

  std::filesystem::path p("D:/sessions/001/recording_0/../../../flight_logs");
  qDebug() << p.lexically_normal().generic_string().c_str();

  QDir q = QDir("D:/sessions/001/recording_0/../../../flight_logs");
  qDebug() << q.canonicalPath();

  QString basePath = "D:/sessions/001/recording_0";

  qDebug() << QDir(basePath + "/../../../flight_logs").canonicalPath();

  return app.exec();
}
