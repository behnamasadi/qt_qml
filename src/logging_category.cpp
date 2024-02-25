#include <QApplication>
#include <QDebug>
#include <QString>

#include "driverUsb.hpp"

// In a source file
Q_LOGGING_CATEGORY(driverUsb, "driver.usb")

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  qSetMessagePattern(
      "[%{time yyyy-MM-dd hh:mm:ss.zzz}] [%{type}] [%{category}] %{message}");

  qDebug() << "Debug message";

  qWarning() << "Warning message";
  qCritical() << "Critical message";
  // qFatal() << "d";
  // can also set QT_LOGGING_RULES to cat=false to turn of the message
  // https://stackoverflow.com/questions/62678216/why-would-i-prefer-qcdebug-over-qdebug

  qCInfo(driverUsb) << "Info from driverUsb";
  qCDebug(driverUsb) << "Debug from driverUsb";
  qCWarning(driverUsb) << "Warning message Info from driverUsb";
  qCCritical(driverUsb) << "Critical message from driverUsb";

  // return app.exec();
}
