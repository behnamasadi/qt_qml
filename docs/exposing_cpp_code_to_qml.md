- [Exposing C++ code to QML](#exposing-c---code-to-qml)
  * [Exposing Properties](#exposing-properties)
  * [Exposing Methods and Slots](#exposing-methods-and-slots)
  * [Exposing Signals](#exposing-signals)
  
# Exposing C++ code to QML
Any functionality that is appropriately exposed by a QObject-derived class or a `Q_GADGET` type
is accessible from QML code. Tee followings are accessible from QML:
- properties: i.e. `Q_PROPERTY(Role role READ getRole WRITE setRole NOTIFY roleChanged)`
- methods marks with `Q_INVOKABLE`: i.e. `Q_INVOKABLE void  showMessageToUSer(){}`
- enums registered with `Q_ENUM`: i.e. `enum Role{Dev, Manager, Tester, Fullstack};     Q_ENUM(Role);`
- signals
- slots

## Exposing Properties

```cpp
Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
```

For maximum interoperability with QML, any property that is writable should have an 
associated NOTIFY signal that is emitted whenever the property value has changed. 
This allows the property to be used with property binding

## Exposing Methods and Slots
Any method of a QObject-derived type is accessible from QML code if it is:

- A public method flagged with the `Q_INVOKABLE()` macro
- A method that is a **public Qt slot**

Both of these can be called from QML:

```cpp
Q_INVOKABLE bool postMessage(const QString &msg) 
{
    qDebug() << "Called the C++ method with" << msg;
    return true;
}
```

and

```cpp
public slots:
void refresh() 
{
    qDebug() << "Called the C++ slot";
}
```


on QML side:

```
MouseArea {
        anchors.fill: parent
        onClicked: {
            var result = msg.postMessage("Hello from QML")
            console.log("Result of postMessage():", result)
            msg.refresh()
        }
    }
```
[source](../qml/message.qml)


## Exposing Signals
Any public signal of a QObject-derived type is accessible from QML code.
The QML engine automatically creates a signal handler for any signal of a QObject-derived type that is used from QML. 
Signal handlers are always named:

`on<Signal>` 

where `<Signal>` is the name of the signal, with the **first letter capitalized**. All parameters passed by the signal are 
available in the signal handler through the parameter names.

Example on cpp side:

```cpp
class PingProcess : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:


signals:
    void output(QString data);

};
```
on the QML side:

```
Label {
    id: pingResult
    Connections {
        target: _pinger
        function onOutput(message) {
            pingResult.text = message
        }
    }
}
```

[source](../src/pinger_qprocess.cpp)



Refs: [1](https://doc.qt.io/qt-6/qtqml-cppintegration-exposecppattributes.html)
