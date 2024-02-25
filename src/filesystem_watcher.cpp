#include <QCoreApplication>
#include <QFileSystemWatcher>

#include <QDebug>
#include <QDirIterator>
#include <QEventLoop>
#include <QFileSystemWatcher>
#include <QObject>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  // const QStringList &paths, QObject *parent = nullptr

  // QFileSystemWatcher watchdog(const QStringList &paths, QObject *parent =
  // nullptr);

  QFileSystemWatcher watchdog;

  watchdog.addPath(QString("C:\\Users\\basadi\\AppData\\Local\\Temp"));

  QEventLoop loop;

  QObject::connect(&watchdog, &QFileSystemWatcher::directoryChanged,
                   [](const QString &path) {
                     QDirIterator it(path, {"*.*"}, // Filter: *.*
                                     QDir::Files);  // Files only

                     while (it.hasNext()) // List all txt files
                     {                    // on console
                       qDebug() << it.next();
                     }
                   });

  QObject::connect(&watchdog, &QFileSystemWatcher::directoryChanged, &loop,
                   &QEventLoop::quit);

  loop.exec();

  qDebug() << "xx";

  a.exec();

  return 0;
}
