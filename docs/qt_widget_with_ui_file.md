

```
# set(SOURCES src/mainwindow.cpp src/main.cpp)
# qt5_wrap_ui(SOURCES UI/mainwindow.ui)
# add_executable(main ${SOURCES})

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_executable(main src/mainwindow.ui src/mainwindow.cpp src/main.cpp qml.qrc)
target_link_libraries(main Qt5::Widgets)
```


Refs: [1](https://doc.qt.io/qt-5/cmake-get-started.html), [2](https://doc.qt.io/qt-5/designer-using-a-ui-file.html), [3](https://stackoverflow.com/questions/50035662/how-to-make-gui-qt-project-with-cmake-in-qt-creator-with-ui-files)

