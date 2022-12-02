# Exposing C++ code to QML


any functionality that is appropriately exposed by a QObject-derived class or a Q_GADGET type
is accessible from QML code.
This enables C++ data and functions to be accessible directly from QML,
often with little or no modification.

The QML engine has the ability to introspect QObject instances through the meta-object system.
This means any QML code can access the following members of an instance of a QObject-derived class

- Properties
- Methods (providing they are public slots or flagged with Q_INVOKABLE)
- Signals

## Exposing Properties

```cpp
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

```

For maximum interoperability with QML, any property that is writable should have an 
associated NOTIFY signal that is emitted whenever the property value has changed. 
This allows the property to be used with property binding



## Exposing Methods and Qt Slots

Any method of a QObject-derived type is accessible from QML code if it is:

- A public method flagged with the Q_INVOKABLE() macro
- A method that is a public Qt slot

Both of these can be called from QML:

```cpp

    Q_INVOKABLE bool postMessage(const QString &msg) {
        qDebug() << "Called the C++ method with" << msg;
        return true;
    }
public slots:
    void refresh() {
        qDebug() << "Called the C++ slot";
    }

```
## Exposing Signals
Any public signal of a QObject-derived type is accessible from QML code.
The QML engine automatically creates a signal handler for any signal of a QObject-derived type that is used from QML. 
Signal handlers are always named on<Signal> where <Signal> is the name of the signal,
 with the first letter capitalized. All parameters passed by the signal
 are available in the signal handler through the parameter names.




Refs: [1](https://doc.qt.io/qt-6/qtqml-cppintegration-exposecppattributes.html)