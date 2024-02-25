#include <QByteArray>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  QByteArray value = qgetenv("MY_ENV_VARIABLE");
  if (!value.isEmpty()) {
    qDebug() << "Value of MY_ENV_VARIABLE:" << value;
  } else {
    qDebug() << "MY_ENV_VARIABLE is not set.";
  }

  //  return app.exec();
}
