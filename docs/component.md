# Component QML Type
Components are reusable, encapsulated QML types.

create one:
```
Rectangle
{
    border.color: "green"
    radius:4;
    smooth: true;
    clip: true;
    color: "white";
    TextInput
    {
        id: childInputText;
        //text: "Enter text..."
        text:parent.text;
        opacity: 0.5;
        anchors.fill: parent;
        anchors.margins: 2
        color:  focus ? "black" : "gray"
        font.pixelSize:parent.height -4;

    }
}
```
Components are often defined by component files, it should be stored in a file that start with **capital letter**: `LineEdit.qml`

Use it:

```
visible: true;
LineEdit
{
    id:lineEdit
    text: "Enter text..."
}
Text {
    anchors.top: lineEdit.bottom
    id: txtFromLineEdit
    text: "summery "+lineEdit.text;
}
```
    
[source](../src/component_loader.cpp)

Refs: [1](https://www.youtube.com/watch?v=qzSNju-h1pk), [2](https://doc.qt.io/qt-6/qml-qtqml-component.html#details), [3](https://www.google.com/search?q=qml+component&oq=qml+component&aqs=chrome.0.69i59j0i512l4j69i60l3.2345j0j1&sourceid=chrome&ie=UTF-8#fpstate=ive&vld=cid:1bd5cafe,vid:cj3v2cu5yUA)



components to be defined inline, within a QML document, here is a component that is used by multiple Loader objects:

```
import QtQuick 2.0

Item {
    width: 100; height: 100

    Component {
        id: redSquare

        Rectangle {
            color: "red"
            width: 10
            height: 10
        }
    }

    Loader { sourceComponent: redSquare }
    Loader { sourceComponent: redSquare; x: 20 }
}
```

# QQmlComponent


```
  QGuiApplication app(argc, argv);
  QQmlEngine *engine = new QQmlEngine;
  QQmlComponent component(engine, QUrl("qrc:/qml/simple_quickview.qml"));

  QObject *myObject = component.create();
  QQuickItem *item = qobject_cast<QQuickItem *>(myObject);
  int width = item->width(); // width = 200
  std::cout << width << std::endl;
```

[source](../src/component.cpp)


Refs: [1](https://doc.qt.io/qt-6/qqmlcomponent.html)

