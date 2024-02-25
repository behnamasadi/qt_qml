#include "counter.hpp"
#include <QApplication>
#include <QGuiApplication>
#include <QMessageBox>
#include <thread>

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);
  Counter a, b;

  // old syntax
  // QObject::connect(&a, SIGNAL( valueChanged( int) ), &b, SLOT(
  // valueNotification(  ) ));

  QObject::connect(&a, &Counter::valueChanged, &b, &Counter::valueNotification);
  QObject::connect(&a, &Counter::valueChanged, [=](int newValue) {
    QMessageBox msgBox;
    msgBox.setText(QString::number(newValue));
    msgBox.exec();
  });

  /* connect(sender, &Sender::valueChanged,     someFunction );*/
  /*
  connect(sender, &Sender::valueChanged,  std::bind( &Receiver::updateValue,
  receiver, "senderValue", std::placeholders::_1 ));
*/
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  a.setValue(2);

  return app.exec();
}
