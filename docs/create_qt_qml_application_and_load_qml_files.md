# Create QT/QML Application and load QML files
## 1. Create QT/QML Application
### 1.1. QCoreApplication 
base class. Use it in command line applications.


### 1.2. QApplication 
base class + GUI + support for widgets. Use it in `QtWidgets` applications.

### 1.3. QGuiApplication 
base class + GUI capabilities. Use it in QML applications.


## 2. Loading QML File


A QML document can be loaded with:

### 2.1. QQmlComponent

`QQmlComponent`: loads a QML document as a C++ object that can then be modified from C++ code.

```cpp
  QGuiApplication app(argc, argv);
  QQmlEngine *engine = new QQmlEngine;
  QQmlComponent component(engine, QUrl("qrc:/qml/simple_quickview.qml"));

  QObject *myObject = component.create();
  QQuickItem *item = qobject_cast<QQuickItem *>(myObject);
  int width = item->width(); // width = 200
  std::cout << width << std::endl;
```

[source](../src/component.cpp)  




### 2.2. QQuickView
`QQuickView` loads any QML type which inherits `Item`. `QQuickView` is generally used to integrate a displayable QML object into an application's user interface.

```
QQuickWindow* window = (QQuickWindow*) engine.rootObjects().first();
```


```cpp
QGuiApplication app(argc, argv);
QQuickView view;
view.setSource(QUrl("qrc:/qml/simple_quickview.qml"));
```

or 

```cpp
view.setSource(QUrl::fromLocalFile("qml/simple_quickview.qml"));
```


`QQuickView` is convenience subclass of `QQuickWindow`.

### 2.3. QQmlApplicationEngine

`QQmlApplicationEngine` can only load QML files which have root component as `Window` or `ApplicationWindow` while `QQuickView` loads any QML type which inherits `Item`.
 
```
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  engine.load(QUrl("qrc:/qml/application_window.qml"));
  QObject *topLevel = engine.rootObjects().value(0);
  QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
  window->show();
  return app.exec();
```

 
[source](src/loading_qml.cpp)


## 3. QML Window vs ApplicationWindow
`ApplicationWindow` is a Window that adds convenience for positioning items, such as `MenuBar`, `ToolBar`, and `StatusBar` in a platform independent manner.
so you can have this:

```
ApplicationWindow
{
    visible: true
    width: 280; height: 280

    menuBar: MenuBar {
          Menu {}
    }
}
```
[source](../src/application_window.cpp)

but you can't have `MenuBar` in `Window`

```
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

}
``` 
[source](../src/window.cpp)

