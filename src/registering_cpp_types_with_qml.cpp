#include "piechart.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QtQml/qqml.h>

//#include <QtQml/qqmlregistration.h> // for qt6

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  qmlRegisterType<PieChart>("Charts", 1, 0, "PieChart");

  QQuickView view;
  view.setResizeMode(QQuickView::SizeRootObjectToView);
  view.setSource(QUrl("qrc:/qml/pie_chart.qml"));

  view.show();
  return app.exec();
}
