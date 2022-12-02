# Registering C++ Types with the QML Type System

A QObject-derived class can be registered with the QML type system to enable the type to be used as a data type from within QML code.


To register a QObject-derived class as an instantiable QML object type, add QML_ELEMENT or QML_NAMED_ELEMENT(<name>) to 
the class declaration and CONFIG += qmltypes, a QML_IMPORT_NAME, and a QML_IMPORT_MAJOR_VERSION to your project file. 
Refs: [1](https://doc.qt.io/qt-6/qtqml-cppintegration-definetypes.html#registering-c-types-with-the-qml-type-system)

## How to use QML_ELEMENT with cmake
Refs: [1](https://stackoverflow.com/questions/63509161/how-to-use-qml-element-with-cmake)



