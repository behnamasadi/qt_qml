cmake_minimum_required(VERSION 3.14)

project(qt_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Widgets)
message( "QT version: "    ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}    )



add_executable(property_context src/property_context.cpp src/user.cpp qml.qrc)
target_link_libraries(property_context PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(loading_qml src/loading_qml.cpp qml.qrc)
target_link_libraries(loading_qml  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(list_view src/list_view.cpp qml.qrc)
target_link_libraries(list_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(grid_view src/grid_view.cpp qml.qrc)
target_link_libraries(grid_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot_qml src/signal_slot_qml.cpp qml.qrc src/user.cpp)
target_link_libraries(signal_slot_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot src/signal_slot.cpp src/counter.cpp)
target_link_libraries(signal_slot PRIVATE Qt${QT_VERSION_MAJOR}::Core)

add_executable(receiving_signals_with_signal_handlers src/receiving_signals_with_signal_handlers.cpp qml.qrc src/person.cpp  src/database.cpp)
target_link_libraries(receiving_signals_with_signal_handlers PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(property_change_signal_handlers src/property_change_signal_handlers.cpp qml.qrc)
target_link_libraries(property_change_signal_handlers PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(property_binding src/property_binding.cpp qml.qrc)
target_link_libraries(property_binding PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(property_system_example src/property_system_example.cpp src/property_system.cpp qml.qrc)
target_link_libraries(property_system_example PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(application_window src/application_window.cpp qml.qrc)
target_link_libraries(application_window PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot_widget src/signal_slot_widget.cpp src/mytimer.cpp)
target_link_libraries(signal_slot_widget  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(qt_quick_input_handlers src/qt_quick_input_handlers.cpp)
target_link_libraries(qt_quick_input_handlers  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(qml_declrative_imperative src/qml_declrative_imperative.cpp)
target_link_libraries(qml_declrative_imperative  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(positioning src/positioning.cpp)
target_link_libraries(positioning  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(delegate_model src/delegate_model.cpp)
target_link_libraries(delegate_model  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(component src/component.cpp)
target_link_libraries(component  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(pinger_qprocess src/pinger_qprocess.cpp  src/PingProcess.cpp qml.qrc)
target_link_libraries(pinger_qprocess PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(sandbox  src/sandbox.cpp )
target_link_libraries(sandbox PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(qqmlengine  src/qqmlengine.cpp )
target_link_libraries(qqmlengine PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(data_type_conversion_cpp_qml  src/data_type_conversion_cpp_qml.cpp)
target_link_libraries(data_type_conversion_cpp_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(exposing_cpp_types_to_qml  src/exposing_cpp_types_to_qml.cpp  src/message.cpp qml.qrc)
target_link_libraries(exposing_cpp_types_to_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(registering_cpp_types_with_qml  src/registering_cpp_types_with_qml.cpp src/piechart.cpp qml.qrc)
target_link_libraries(registering_cpp_types_with_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(q_gadget  src/q_gadget.cpp)
target_link_libraries(q_gadget PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(q_object  src/q_object.cpp)
target_link_libraries(q_object PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(signal_slot_lambda  src/signal_slot_lambda.cpp src/counter.cpp)
target_link_libraries(signal_slot_lambda PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(q_list_view  src/q_list_view.cpp)
target_link_libraries(q_list_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(q_table_view  src/q_table_view.cpp src/customTableModel.cpp)
target_link_libraries(q_table_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(qml_table_view  src/qml_table_view.cpp src/customTableModel.cpp)
target_link_libraries(qml_table_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(q_tree_view src/q_tree_view.cpp)
target_link_libraries(q_tree_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )

add_executable(custom_item_model src/custom_item_model.cpp)
target_link_libraries(custom_item_model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets )


