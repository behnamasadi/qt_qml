#  Handle Events


## Receiving Signals With Signal Handlers

```
import QtQuick
import QtQuick.Controls

Rectangle {
    id: rect
    width: 250; height: 250

    Button {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Change color!"
        onClicked: {
            rect.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        }
    }
}
```

another example:

```
Rectangle {
    width: 600
    height: 800
    MouseArea {
        anchors.fill: parent
        onClicked: {
            // return a gadget back to c++
            _db.addPerson(_db.makePerson("Behnam", 18))

            // return a gadget from c++
            var behnam = _db.lookPerson("behnam")

            //accessing a global gadget
            //console.log("global lookup", behnam.name)
            //console.log(behnam.name)

            //updating a gadget
        }
    }
}
```

[source](../src/receiving_signals_with_signal_handlers.cpp)


Refs: [1](https://doc.qt.io/qt-6/qtqml-syntax-signals.html#receiving-signals-with-signal-handlers)

## MouseArea  

## Flickable

## Qt Quick Input Handlers
Qt Quick Input Handlers are a set of QML types used to handle events from keyboard, touch, mouse, and stylus devices in a UI. In contrast to event-handling items, such as MouseArea and Flickable, input handlers are explicitly non-visual

[source](src/qt_quick_input_handlers.cpp)




Refs: [1](https://doc.qt.io/qt-6/qtquickhandlers-index.html)
