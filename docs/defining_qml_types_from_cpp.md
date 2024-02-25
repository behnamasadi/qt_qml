# Defining QML Types from C++
A C++ class can be registered with the QML type system to enable the class to be used as a data type within QML code. Exposing the   [properties, methods and signals of any QObject-derived class ](defining_qml_types_from_cpp.md) to QML is not enough for that class to be used as a data type from QML and it has to be  **registered** with the type system.


# Registering an Object Type
A C++ code can be registered to QML in a variety of ways:

1. The class can be [registered as an instantiable QML type](https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html#registering-an-instantiable-object-type), so that it can be instantiated and used like any ordinary QML object type from QML code

2. The class can be registered as a [Singleton Type](https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html#registering-singleton-objects-with-a-singleton-type) so that a single instance of the class may be imported from QML.

3. An instance of the class can be [embedded into QML](https://doc.qt.io/qt-6/qtqml-cppintegration-contextproperties.html) code as a context property or context object, allowing the instance's properties, methods and signals to be accessed from QML


## 1. Registering an Instantiable QML Object Type

Any QObject-derived C++ class can be registered as the definition of a QML object type. 

1. If the class just represented some data type and was not an item that actually needed to be displayed, it could simply inherit from `QObject`.

2. If we need to perform drawing operations we need to inherit `QQuickPaintedItem` because we want to override `QQuickPaintedItem::paint()` .  

3. If we want to create a visual item that doesn't need to perform drawing operations with the `QPainter` API, we can just subclass `QQuickItem`.

4. If we want to extend the functionality of an existing QObject-based class, it could inherit from that class instead. 


### 1.1 Registering an Instantiable Data type Without Display

```cpp
#include <QtQml/qqml.h>

class MyMessageType : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
QString text();
void setText(QString text);

signals:
void textChanged();

private:
QString m_text;
};
```
on the application:

```cpp
int versionMajor = 2;
int versionMinor = 7;
qmlRegisterType<MyMessageType>("com.mycompany.qmlcomponents", versionMajor,
                         versionMinor, "Message");
QQuickView view;
view.setSource(QUrl("qrc:/qml/MyMessageType.qml"));
view.show();
```
and in the qml side:

```
import com.mycompany.qmlcomponents 2.7

Message {
    text: "foo"
    creationDate: new Date()
}
```
[source](../src/defining_qml_types_from_cpp.cpp)


### 1.2 Registering an Instantiable Data type With Display Inherited From QQuickPaintedItem


```cpp
#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class PieChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    QML_ELEMENT

public:
    PieChart(QQuickItem *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter);

private:
    QString m_name;
    QColor m_color;
};
```

Now we have implement `paint()` function:

```cpp
void PieChart::paint(QPainter *painter)
{
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}
```

we can implement other drawing functions:

```
void PieChart::paint(QPainter *painter) {
  QPen pen(m_color, 2);
  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);

  QPolygon qpolygon;

  qpolygon.append(QPoint(20, 3));
  qpolygon.append(QPoint(8, 9));
  qpolygon.append(QPoint(45, 30));
  qpolygon.append(QPoint(15, 50));
  painter->drawPoints(qpolygon);
}
```

and in the qml side:

```
PieChart {
    id: chartA
    anchors.top: parent.top
    anchors.left: parent.left
    width: 100
    height: 100
    name: "chartA"
    //color: "red"
    color: chartB.color

    //ChartCleared is a signal so it can be called
    onChartCleared: console.log("The chart has been cleared")
}
```
Refs: [1](https://doc.qt.io/qt-5/qtqml-tutorials-extending-qml-example.html)

[source](../src/registering_cpp_types_with_qml.cpp)



## 2. Registering a Singleton Type



## 3. Embedding a Class Into QML




Refs: [1](https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html), [2](https://doc.qt.io/qt-6/qtqml-tutorials-extending-qml-example.html)
