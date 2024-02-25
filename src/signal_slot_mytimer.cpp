#include "mytimer.h"
#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  mytimer mytimer_object;

  app.exec();
}
