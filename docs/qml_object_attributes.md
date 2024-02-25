# QML Object Attributes

Every QML object type has a defined set of attributes. There are several different kinds of attributes which can be specified, which are described below:


## Property Attributes
A property is an attribute of an object that can be assigned a static value or bound to a dynamic expression. A property's value can be read/ modified by other objects. 

### Defining Property Attributes
In cpp

```
Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
```

In qml (Property names must begin with a lower case letter)
```
[default] [required] [readonly] property <propertyType> <propertyName>
```

var value type is a generic placeholder:
```
property var someBool: true
property var someList: [1, 2, "three", "four"]
property var someObject: Rectangle { width: 100; height: 100; color: "red" }
```

### Property Change Signal Handlers

Declaring a custom property implicitly creates a signal handler called `on<PropertyName>Changed`, for instance:

```
Rectangle {
    property color previousColor
    property color nextColor
    onNextColorChanged: console.log("The next color will be: " + nextColor.toString())
}
```


#### Value Assignment
There are two kinds of values which may be assigned to a property: `static values`, and `binding expression values aka property bindings`:


```
Rectangle {
    // both of these are static value assignments on initialization
    width: 400
    height: 200

    Rectangle {
        // both of these are binding expression value assignments on initialization
        width: parent.width / 2
        height: parent.height
    }
}
```
 

Refs: [1](https://doc.qt.io/qt-6/qtqml-syntax-objectattributes.html#property-attributes)



### Property Binding

```
import QtQuick 2.12

Rectangle {
    color:"green";
    //color:"#<alpha><rr><gg><bb>";
    // color: Qt.rgba(0, .05, 0, 1)
    width: child.width
    height: child.height

    Image {
        id: child
        source: "../images/PNG_transparency_demonstration_1.png"
        anchors.margins: 5
        anchors.fill: parent
        anchors.centerIn: parent
    }
}
```
This will give us the `Binding loop detected` error:
```
QML Rectangle: Binding loop detected for property "width"
QML Rectangle: Binding loop detected for property "height"
```
to solve this:

```
Rectangle {
    implicitWidth: child.implicitWidth
    implicitHeight: child.implicitHeight
    color:"green";
    width: child.width
    height: child.height
    Image {
        id: child
        source: "../images/PNG_transparency_demonstration_1.png"
        anchors.margins: 5
        anchors.fill: parent
        anchors.centerIn: parent
        width:parent.implicitWidth;
        height:parent.implicitheight;
    }
}
```

[source](../src/property_context.cpp)

### Property Aliases
Property aliases are properties which hold a reference to another property. Alias connects the newly declared property (called the aliasing property) as a direct reference to an existing property (the aliased property). A property alias declaration looks like an ordinary property definition, except that it requires the alias keyword instead of a property type, and the right-hand-side of the property declaration must be a valid alias reference:


```
[default] property alias <name>: <alias reference>
```
Aliases to properties that are up to two levels deep will work:

```
property alias color: rectangle.border.color

Rectangle {
    id: rectangle
}
```

Aliases are only activated once a component has been fully initialized

```
property alias widgetLabel: label

//will generate an error
//widgetLabel.text: "Initial text"

//will generate an error
//property alias widgetLabelText: widgetLabel.text

Component.onCompleted: widgetLabel.text = "Alias completed Initialization"
```

[source](../src/alias.cpp) 


### Property System

```cpp
class <className> : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    void setPriority(Priority priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const
    { return m_priority; }

signals:
    void priorityChanged(Priority);
private:
    Priority m_priority;
};
```


### Property Context

The under line at beginning of variable is just a convention to emphasis it is coming from cpp to the qml file

```cpp
QGuiApplication app(argc, argv);
QQuickView view;
QQmlContext *context = view.rootContext();

context->setContextProperty("_aString", QString("AAAA"));
context->setContextProperty("_aSize", QSize(400, 600));

User *currentuser = new User("foo", 10, User::Dev);
context->setContextProperty("_currentuser", currentuser);
```
in the qml side:

```
Rectangle {
    width: _aSize.width
    height: _aSize.height

    Column {
        anchors.centerIn: parent
        spacing: 10
        Text {
            text: _currentuser.name
        }
        Text {
            text: _currentuser.age
        }
        Text {
            text: _currentuser.role
        }
    }
}
```
[source](../src/property_context.cpp)


Refs: [1](https://doc.qt.io/qt-6/qqmlcontext.html#details)

## Method Attributes
A method may be defined for a type in C++ 

```
Q_INVOKABLE bool postMessage(const QString &msg) { qDebug() << "Called the C++ method with" << msg;   return true; }
```

or by registering it as a `Q_SLOT` 
```
Q_SLOT
```
for more read [here](https://doc.qt.io/qt-6/qobject.html#Q_SLOT)


or in a QML document:

```
function <functionName>([<parameterName>[: <parameterType>][, ...]]) [: <returnType>] { <body> }
```

for example:

```
import QtQuick 2.0

Item {
    width: 200; height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: (mouse)=> label.moveTo(mouse.x, mouse.y)
    }

    Text {
        id: label

        function moveTo(newX: real, newY: real) {
            label.x = newX;
            label.y = newY;
        }

        text: "Move me!"
    }
}
```



## Signal Attributes

A signal may be defined for a type in C++ by registering a `Q_SIGNAL` 


```cpp
Q_SIGNAL
```

or in the qml:

```
signal <signalName>[([<parameterName>: <parameterType>[, ...]])]
```
for example:

```
import QtQuick 2.0

Item {
    signal clicked
    signal hovered()
    signal actionPerformed(action: string, actionResult: int)
}
```


Refs: [1](https://doc.qt.io/qt-6/qtqml-syntax-objectattributes.html#defining-signal-attributes)

## Signal Handler Attributes
Signal handlers are a special sort of **method attribute**, where the method implementation is invoked by the QML engine whenever the associated signal is emitted. 


