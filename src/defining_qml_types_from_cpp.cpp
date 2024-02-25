#include "MyMessageType.hpp"
#include <QGuiApplication>
#include <QQuickView>

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);
  int versionMajor = 2;
  int versionMinor = 7;
  qmlRegisterType<MyMessageType>("com.mycompany.qmlcomponents", versionMajor,
                                 versionMinor, "Message");
  QQuickView view;

  view.setSource(QUrl("qrc:/qml/MyMessageType.qml"));
  view.show();
  app.exec();
}
