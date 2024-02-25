# QT and QML

This repository contains my snippets for developing QT widgets and QML applications.

## Building and Installation

if you need to update your cmake:

Navigate to [CMake's official](https://cmake.org/download/) website to get the link for the latest source tarball

```
./bootstrap
make -j$(nproc)
sudo make install
sudo update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
```

### How to build on your machine

configure it:

```
cmake -G "Ninja Multi-Config"  -S . -B build
```

build it:

```
cmake --build build --config Release
```

or 

```
cmake --build build --config Debug
```

or be more specific:

```
cmake --build build --target all --config Release
```

If you prefer `preset` use:

```
cmake --preset ninja-multi
```
and 

```
cmake --build --preset ninja-multi-debug
```
or 
```
cmake --build --preset ninja-multi-release
```



- [Create QT/QML Application and load QML files](docs/create_qt_qml_application_and_load_qml_files.md)
  - [1. Create QT/QML Application](docs/create_qt_qml_application_and_load_qml_files.md#1-create-qt-qml-application)
    - [1.1. QCoreApplication](docs/create_qt_qml_application_and_load_qml_files.md#11-qcoreapplication)
    - [1.2. QApplication](docs/create_qt_qml_application_and_load_qml_files.md#12-qapplication)
    - [1.3. QGuiApplication](docs/create_qt_qml_application_and_load_qml_files.md#13-qguiapplication)
  - [2. Loading QML File](docs/create_qt_qml_application_and_load_qml_files.md#2-loading-qml-file)
    - [2.1. QQmlComponent](docs/create_qt_qml_application_and_load_qml_files.md#21-qqmlcomponent)
    - [2.2. QQuickView](docs/create_qt_qml_application_and_load_qml_files.md#22-qquickview)
    - [2.3. QQmlApplicationEngine](docs/create_qt_qml_application_and_load_qml_files.md#23-qqmlapplicationengine)
  - [3. QML Window vs ApplicationWindow](docs/create_qt_qml_application_and_load_qml_files.md#3-qml-window-vs-applicationwindow)
- [QT Widget With UI File](docs/qt_widget_with_ui_file.md)
- [QQmlEngine](docs/qqmlengine.md)
- [Component](docs/component.md)
- [Signal and Slot](docs/signal_slot.md#signal-and-slot)
  - [Signal Slot Syntax](docs/signal_slot.md#signal-slot-syntax)
  - [Connecting to a Function](docs/signal_slot.md#connecting-to-a-function)
  - [Connecting to a Lambda](docs/signal_slot.md#connecting-to-a-lambda)
  - [QWidget Signal and Slot](docs/signal_slot.md#qwidget-signal-and-slot)
  - [QML Signal and Slot](docs/signal_slot.md#qml-signal-and-slot)
  - [Create a Signal Slot Connection in QML File](docs/signal_slot.md#create-a-signal-slot-connection-in-qml-file)
  - [Where to connect/ disconnect signals to/ from slots](docs/signal_slot.md#where-to-connect--disconnect-signals-to--from-slots)
- [Handle Events](docs/handle_events.md#handle-events)
  - [Receiving Signals With Signal Handlers](docs/handle_events.md#receiving-signals-with-signal-handlers)
  - [MouseArea](docs/handle_events.md#mousearea)
  - [Flickable](docs/handle_events.md#flickable)
  - [Qt Quick Input Handlers](docs/handle_events.md#qt-quick-input-handlers)
- [JavaScript Expressions in QML Documents](docs/javascript_expressions_in_qml_documents.md)
  - [The Body of Property Bindings](docs/javascript_expressions_in_qml_documents.md#the-body-of-property-bindings)
  - [JavaScript in Signal Handlers](docs/javascript_expressions_in_qml_documents.md#javascript-in-signal-handlers)
  - [JavaScript in Standalone Functions](docs/javascript_expressions_in_qml_documents.md#javascript-in-standalone-functions)
- [Action QML Type](docs/action_qml_type.md)
- [Exposing C++ Signals, Methods, Slots and Properties to QML](docs/exposing_cpp_code_to_qml.md)
  - [Exposing Properties](docs/exposing_cpp_code_to_qml.md#exposing-properties)
  - [Exposing Methods and Slots](docs/exposing_cpp_code_to_qml.md#exposing-methods-and-slots)
  - [Exposing Signals](docs/exposing_cpp_code_to_qml.md#exposing-signals)
- [Defining and Registering QML Types from C++ Code](docs/defining_qml_types_from_cpp.md)
  - [1. Registering an Instantiable QML Object Type](docs/defining_qml_types_from_cpp.md#1-registering-an-instantiable-qml-object-type)
    - [1.1 Registering an Instantiable Data type Without Display](docs/defining_qml_types_from_cpp.md#11-registering-an-instantiable-data-type-without-display)
    - [1.2 Registering an Instantiable Data type With Display Inherited From QQuickPaintedItem](#12-registering-an-instantiable-data-type-with-display-inherited-from-qquickpainteditem)
  - [2. Registering a Singleton Type](docs/defining_qml_types_from_cpp.md#2-registering-a-singleton-type)
  - [3. Embedding a Class Into QML](docs/defining_qml_types_from_cpp.md#3-embedding-a-class-into-qml)
- [Interacting with QML Objects from C++](docs/interacting_with_qml_objects_from_cpp.md)
- [QML and C++ Data Type Conversion](docs/data_type_conversion_cpp_qml.md)
- [QML and C++ Integration](docs/qml_and_cpp_integration.md)
- [QQuickItem, Item QML Type](docs/item_qml_type.md)
- [QML Object Attributes](docs/qml_object_attributes.md)
- Menu Bar
- QML Layout
  - [ColumnLayout]()
  - [GridLayout](src/grid_view.cpp)
  - [Listview Layout](src/list_view.cpp)
  - [RowLayout]()
  - [StackLayout]()
- Positioning
  - [Manual Positioning]()
  - [Anchors](https://doc.qt.io/qt-6/qtquick-positioning-anchors.html)
- [Declarative vs Imperative QML](https://www.qmlpoison.com/2020/05/post1.html)
- [Prototyping with qmlscene](https://doc.qt.io/qt-5/qtquick-qmlscene.html)
- [GammaRay](https://www.kdab.com/development-resources/qt-tools/gammaray/)
- [QProcess](src/pinger_qprocess.cpp)
- [Model/View in Qt Quick](docs/model_view.md)
  - [QTreeView](src/q_tree_view.cpp)
  - [QML TreeView]()
  - [QAbstractListModel](docs/q_abstract_list_model.md)
  - [QAbstractProxyModel](docs/q_abstract_proxy_model.md)
  - [QSortFilterProxyModel](docs/q_sort_filter_proxy_model.md)
  - [QAbstractItemModel](docs/q_abstract_item_model.md)
  - [QAbstractItemView](docs/q_abstract_item_view.md)
  - [QAbstractItemDelegate](docs/q_abstract_item_delegate.md)
  - [QML Table View](src/qml_table_view.cpp)
  - [QTableView](src/customTableModel.cpp)
  - [QAbstractTableModel](docs/q_abstract_table_model.md)
  - [QStandardItemModel, QStandardItem, QModelIndex](docs/q_standard_item_model_q_model_index.md)
  - [ListModel, Listview](docs/list_model_list_view.md)
  - [rowsInserted,rowsRemoved,dataChanged](docs/rowsInserted_rowsRemoved_dataChanged.md)
- [Oauth2](docs/oauth2.md)
- [QtNetwork](docs/network.md)
  - [HTTP Request Methods](docs/network.md#http-request-methods)
  - [QHttpMultiPart](docs/network.md#qhttpmultipart)
  - [QNetworkAccessManager](docs/network.md#qnetworkaccessmanager)
  - [QNetworkRequest](docs/network.md#qnetworkrequest)
  - [QNetworkReply](docs/network.md#qnetworkreply)
  - [Network Examples](docs/network.md#network-examples)
  - [Postman Example](src/postman_example.cpp)
- [Multithreading Technologies in Qt](docs/multithreading_technologies_in_qt.md)
- [Logging Category](docs/logging_category_in_qt.md)
- [QQuickImageProvider](docs/image_provider.md)
- [JSON](docs/qjson.md)
- [OpenCV Qt Image Conversion](src/opencv_qt_image_conversion.cpp)
- [Settings and Standard Path](src/settings_standard_path.cpp)
- [QIODevice](src/QIODevice_example.cpp)
- [Slider](docs/slider.md)
- [Filesystem Watcher](src/filesystem_watcher.cpp)
- [SplitView](docs/splitview.md)
- [Qml PCL](src/qml_pcl.cpp)
- [QQuickVTKRender](src/QQuickVTKRender.cpp)
- [QVariant](docs/qVariant.md)
- [Qt Quick Controls Version](docs/qt_quick_controls_version.md)
- [Environmental Variable In Qt](docs/environmental_variable_in_qt.md)

Refs: [1](https://www.youtube.com/playlist?list=PL6CJYn40gN6hdNC1IGQZfVI707dh9DPRc), [2](https://github.com/KDAB/kdabtv/tree/master/qml-intro)
