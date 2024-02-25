/*
Each QML component is instantiated in a QQmlContext. QQmlContext's are essential
for passing data to QML components. In QML, contexts are arranged hierarchically
and this hierarchy is managed by the QQmlEngine.

Prior to creating any QML components,
an application must have created a QQmlEngine to gain access to a QML context.

*/
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQuickItem>

int main(int argc, char **argv) {
  QQmlEngine engine;
  QQmlComponent component(&engine);
  component.setData("import QtQuick 2.0\nText { text: \"Hello world!\" }",
                    QUrl());
  QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
}
