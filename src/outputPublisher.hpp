#include <QObject>
#include <iostream>

class outputPublisher : public QObject {
  Q_OBJECT

public slots:
  void print(QString data) { std::cout << data.toStdString() << std::endl; }
};
