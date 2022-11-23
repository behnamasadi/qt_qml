#include <QGuiApplication>
#include <QQuickView>

/*
1. QCoreApplication - base class. Use it in command line applications.
2. QApplication - base class + GUI + support for widgets. Use it in QtWidgets
applications.
3. QGuiApplication - base class + GUI capabilities. Use it in QML applications.
*/

/*

A QML document can be loaded with
1. QQmlComponent: loads a QML document as a C++ object that can then be modified
from C++ code 2.QQuickView: also does above, but as QQuickView is a
QWindow-derived class, the loaded object will also be rendered into a visual
display; QQuickView is generally used to integrate a displayable QML object into
an application's user interface.

*/

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);
  QQuickView view;
  // both of them work:
  view.setSource(QUrl("qrc:/qml/simple_quickview.qml"));
  // view.setSource(QUrl::fromLocalFile("qml/simple_quickview.qml"));

  view.show();
  return app.exec();
}
