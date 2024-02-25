# JavaScript Expressions in QML Documents
Various parts of QML documents can contain JavaScript code:

## The Body of Property Bindings

There are two ways to define a property binding:

1. property initialization:
```
import QtQuick 2.12

Rectangle {
    id: colorbutton
    width: 200; height: 80;

    color: inputHandler.pressed ? "steelblue" : "lightsteelblue"

    TapHandler {
        id: inputHandler
    }
}
```

2. Using [Qt.binding()](https://doc.qt.io/qt-6/qml-qtqml-qt.html#binding-method) function:

```
import QtQuick 2.12

Rectangle {
    id: colorbutton
    width: 200; height: 80;

    color: "red"

    TapHandler {
        id: inputHandler
    }

    Component.onCompleted: {
        color = Qt.binding(function() { return inputHandler.pressed ? "steelblue" : "lightsteelblue" });
    }
}
```

## JavaScript in Signal Handlers

```
import QtQuick 2.12

Rectangle {
    id: button
    width: 200; height: 80; color: "lightsteelblue"

    TapHandler {
        id: inputHandler
        onTapped: {
            // arbitrary JavaScript expression
            console.log("Tapped!")
        }
    }

    Text {
        id: label
        anchors.centerIn: parent
        text: inputHandler.pressed ? "Pressed!" : "Press here!"
    }
}
```

## JavaScript in Standalone Functions

```
import QtQuick 2.12

Item {
    function fibonacci(n){
        var arr = [0, 1];
        for (var i = 2; i < n + 1; i++)
            arr.push(arr[i - 2] + arr[i -1]);

        return arr;
    }
    TapHandler {
        onTapped: console.log(fibonacci(10))
    }
}
```

Refs: [1](https://doc.qt.io/qt-6/qtqml-javascript-expressions.html)

