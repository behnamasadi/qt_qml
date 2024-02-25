#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char **argv) {
  /*
  QCoreApplication - base class. Use it in command line applications.
  QApplication - base class + GUI + support for widgets. Use it in QtWidgets
  applications. QGuiApplication - base class + GUI capabilities. Use it in QML
  applications.

  */

  /*
  The QQuickView class provides a window for displaying a Qt Quick user
  interface. subclass of QQuickWindow which will automatically load and display
  a QML scene
  */

  // https://youtu.be/quFciLDIxUw?list=PL6CJYn40gN6hdNC1IGQZfVI707dh9DPRc&t=775

  QGuiApplication app(argc, argv);
  QQuickView view;
  // QQmlContext * context= view.engine()->rootContext();
  QQmlContext *context = view.rootContext();
  context->setContextProperty(
      "_aString",
      QString("AAAA")); // the under line is just a convention to emphasis it is
                        // coming from cpp in the qml file
  view.setSource(QUrl::fromLocalFile("../qml_cpp.qml"));
  // const QUrl url(QStringLiteral("qrc:/bg.qml"));
  // view.setSource(url);

  view.show();

  return app.exec();
}
