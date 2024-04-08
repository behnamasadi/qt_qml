cmake_minimum_required(VERSION 3.14)

project(qt_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_AUTOUIC ON)

# "The AUTOMOC target property controls whether cmake inspects the C++ files in the target to determine if they
# require moc to be run, and to create rules to execute moc at the appropriate time." -
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Qml Quick Widgets Gui QuickControls2 Xml Sql PrintSupport Svg Network Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Qml Quick Widgets Gui QuickControls2 Xml Sql PrintSupport Svg Network Concurrent)

message(STATUS "QT version: " ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR})
message(STATUS "QT dir" ${Qt${QT_VERSION_MAJOR}_DIR})


# As of Qt 5.12, this lists the COMPONENT names as follows:
# 3DAnimation             Help                    QuickWidgets
# 3DCore                  LinguistTools           RemoteObjects
# 3DExtras                Location                RepParser
# 3DInput                 Multimedia              Scxml
# 3DLogic                 MultimediaWidgets       Sensors
# 3DQuick                 Network                 SerialPort
# 3DQuickAnimation        Nfc                     Sql
# 3DQuickExtras           OpenGL                  Svg
# 3DQuickInput            OpenGLExtensions        Test
# 3DQuickRender           Positioning             TextToSpeech
# 3DQuickScene2D          PositioningQuick        UiPlugin
# 3DRender                PrintSupport            UiTools
# AndroidExtras           Qml                     WebChannel
# Bluetooth               Quick                   WebSockets
# Concurrent              QuickCompiler           WebView
# Core                    QuickControls2          Widgets
# Gamepad                 QuickTemplates2         Xml
# Gui                     QuickTest               XmlPatterns



include(FetchContent)

# # Fetch VTK
# FetchContent_Declare(
#   vtk
#   GIT_REPOSITORY https://gitlab.kitware.com/vtk/vtk.git
#   GIT_TAG        v9.2.0 # Adjust the tag as needed
# )

# FetchContent_GetProperties(vtk)
# if(NOT vtk_POPULATED)
#   FetchContent_Populate(vtk)
  
#   # Set custom options for VTK configuration
#   set(VTK_REPORT_OPENGL_ERRORS OFF CACHE BOOL "Disable OpenGL error reporting" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_GUISupportQt YES CACHE BOOL "Enable VTK Qt GUI support" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_GUISupportQtQuick YES CACHE BOOL "Enable VTK QtQuick support" FORCE)
#   set(VTK_WRAP_JAVA OFF CACHE BOOL "Disable VTK Java wrapping" FORCE)
#   set(VTK_WRAP_PYTHON OFF CACHE BOOL "Disable VTK Python wrapping" FORCE)
#   set(VTK_ENABLE_WRAPPING OFF CACHE BOOL "Disable all VTK wrapping" FORCE)
#   set(VTK_BUILD_TESTING OFF CACHE BOOL "Disable VTK testing" FORCE)
#   set(VTK_GROUP_ENABLE_Rendering DONT_WANT CACHE STRING "Disable VTK rendering" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_RenderingQt YES CACHE BOOL "Enable VTK Qt rendering" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_hdf YES CACHE BOOL "Enable VTK HDF support" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_IOHDF YES CACHE BOOL "Enable VTK HDF I/O support" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_InteractionImage YES CACHE BOOL "Enable VTK image interaction" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_RenderingLOD YES CACHE BOOL "Enable VTK Level of Detail rendering" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_ViewsCore YES CACHE BOOL "Enable VTK core views" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_ViewsContext2D YES CACHE BOOL "Enable VTK 2D context views" FORCE)
#   set(VTK_MODULE_ENABLE_VTK_RenderingContextOpenGL2 YES CACHE BOOL "Enable VTK OpenGL2 rendering context" FORCE)

#   add_subdirectory(${vtk_SOURCE_DIR} ${vtk_BINARY_DIR})
# endif()



# Set VTK_DIR to the VTK build directory
#set(VTK_DIR ${vtk_BINARY_DIR})




# Find the VTK package to include its targets
#find_package(VTK REQUIRED)

# Include VTK's directories
include_directories(${VTK_INCLUDE_DIRS})

# Link against the VTK libraries
#target_link_libraries(YourTargetName ${VTK_LIBRARIES})



message("VTK_LIBRARIES:" VTK::CommonCore)
message("VTK_INCLUDE_DIRS:" ${VTK_INCLUDE_DIRS})







## Fetch PCL
#FetchContent_Declare(
#  pcl
#  GIT_REPOSITORY https://github.com/PointCloudLibrary/pcl.git
#  GIT_TAG        pcl-1.13.0 # Adjust the tag as needed#
#)
#FetchContent_MakeAvailable(pcl)


#set(VTK_DIR "$ENV{HOME}/usr/lib/cmake/vtk-9.3/")
find_package(VTK QUIET)


if(VTK_FOUND)

  message("VTK_VERSION:" ${VTK_VERSION})
  message("VTK_LIBRARIES:" ${VTK_LIBRARIES})
else()
  #message(FATAL_ERROR "Could not find VTK in specified VTK_DIR")
endif()

set(PCL_DIR "$ENV{HOME}/usr/share/pcl-1.13/")
find_package(PCL QUIET)

if(${PCL_FOUND} AND ${VTK_FOUND})
    include_directories(${PCL_INCLUDE_DIRS})
    link_directories(${PCL_LIBRARY_DIRS})
    add_definitions(${PCL_DEFINITIONS})
    message("VTK_FOUND: " ${VTK_FOUND})
    message("VTK_VERSION: " ${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION})

    message("PCL_FOUND: " ${PCL_FOUND})
    message("PCL_VERSION: " ${PCL_VERSION})
    message("PCL_LIBRARIES: " ${PCL_LIBRARIES})

    add_executable(QQuickVTKRender src/QQuickVTKRender.cpp qml.qrc)
    target_link_libraries(QQuickVTKRender PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets ${VTK_LIBRARIES})

# add_executable(qml_pcl src/qml_pcl.cpp qml.qrc)
# target_link_libraries(qml_pcl PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets ${PCL_LIBRARIES} ${VTK_LIBRARIES})
else()
    message("vtk not found")
    message("pcl not found")
endif()

add_executable(property_context src/property_context.cpp src/user.cpp qml.qrc)
target_link_libraries(property_context PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(loading_qml src/loading_qml.cpp qml.qrc)
target_link_libraries(loading_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(list_view src/list_view.cpp qml.qrc)
target_link_libraries(list_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(grid_view src/grid_view.cpp qml.qrc)
target_link_libraries(grid_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot_qml src/signal_slot_qml.cpp qml.qrc src/user.cpp)
target_link_libraries(signal_slot_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot src/signal_slot.cpp src/counter.cpp)
target_link_libraries(signal_slot PRIVATE Qt${QT_VERSION_MAJOR}::Core)

add_executable(receiving_signals_with_signal_handlers src/receiving_signals_with_signal_handlers.cpp qml.qrc src/person.cpp src/database.cpp)
target_link_libraries(receiving_signals_with_signal_handlers PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(signal_slot_widget src/signal_slot_widget.cpp)
target_link_libraries(signal_slot_widget PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(signal_slot_lambda src/signal_slot_lambda.cpp src/counter.cpp)
target_link_libraries(signal_slot_lambda PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(signal_slot_mytimer src/signal_slot_mytimer.cpp src/mytimer.cpp)
target_link_libraries(signal_slot_mytimer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(property_binding src/property_binding.cpp qml.qrc)
target_link_libraries(property_binding PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(application_window src/application_window.cpp qml.qrc)
target_link_libraries(application_window PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(window src/window.cpp qml.qrc)
target_link_libraries(window PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

# add_executable(simple_quickview src/simple_quickview.cpp qml.qrc)
# target_link_libraries(simple_quickview PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
add_executable(qt_quick_input_handlers src/qt_quick_input_handlers.cpp)
target_link_libraries(qt_quick_input_handlers PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(qml_declrative_imperative src/qml_declrative_imperative.cpp)
target_link_libraries(qml_declrative_imperative PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(positioning src/positioning.cpp)
target_link_libraries(positioning PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(component src/component.cpp qml.qrc)
target_link_libraries(component PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(qqmlengine src/qqmlengine.cpp)
target_link_libraries(qqmlengine PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(exposing_cpp_types_to_qml src/exposing_cpp_types_to_qml.cpp src/message.cpp qml.qrc)
target_link_libraries(exposing_cpp_types_to_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(registering_cpp_types_with_qml src/registering_cpp_types_with_qml.cpp src/piechart.cpp qml.qrc)
target_link_libraries(registering_cpp_types_with_qml PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(q_list_view src/q_list_view.cpp qml.qrc)
target_link_libraries(q_list_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(q_table_view src/q_table_view.cpp src/customTableModel.cpp)
target_link_libraries(q_table_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(qml_table_view src/qml_table_view.cpp src/customTableModel.cpp)
target_link_libraries(qml_table_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(q_tree_view src/q_tree_view.cpp)
target_link_libraries(q_tree_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(custom_item_model src/custom_item_model.cpp)
target_link_libraries(custom_item_model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(settings_standard_path src/settings_standard_path.cpp)
target_link_libraries(settings_standard_path PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(qthread_example src/qthread_example.cpp src/WorkerThread.cpp)
target_link_libraries(qthread_example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(progress_bar src/progress_bar.cpp src/Project.cpp)
target_link_libraries(progress_bar PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(image_provider src/image_provider.cpp)
target_link_libraries(image_provider PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(opencv_qt_image_conversion src/opencv_qt_image_conversion.cpp)
target_link_libraries(opencv_qt_image_conversion PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(json_example src/json_example.cpp)
target_link_libraries(json_example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(network src/network.cpp qml.qrc src/worker.cpp)
target_link_libraries(network PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)

add_executable(postman_example src/postman_example.cpp)
target_link_libraries(postman_example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(filesystem_watcher src/filesystem_watcher.cpp)
target_link_libraries(filesystem_watcher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(QIODevice src/QIODevice_example.cpp)
target_link_libraries(QIODevice PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(standard_paths src/standard_paths.cpp)
target_link_libraries(standard_paths PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

# add_executable(qtnetworkauth_reddit src/qtnetworkauth_reddit.cpp  src/redditmodel.cpp src/redditwrapper.cpp)
# target_link_libraries(qtnetworkauth_reddit PRIVATE  Qt${QT_VERSION_MAJOR}::Widgets   Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)
add_executable(slider src/slider.cpp qml.qrc)
target_link_libraries(slider PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_executable(defining_qml_types_from_cpp src/defining_qml_types_from_cpp.cpp src/MyMessageType.cpp qml.qrc)
target_link_libraries(defining_qml_types_from_cpp PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(qt_concurrent_thread_example src/qt_concurrent_thread_example.cpp)
target_link_libraries(qt_concurrent_thread_example PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Concurrent)

add_executable(component_loader src/component_loader.cpp qml.qrc)
target_link_libraries(component_loader PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(split_view src/split_view.cpp qml.qrc)
target_link_libraries(split_view PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(actions src/actions.cpp qml.qrc)
target_link_libraries(actions PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

# add_executable(pinger_qprocess src/pinger_qprocess.cpp src/PingProcess.cpp qml.qrc)
# target_link_libraries(pinger_qprocess PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)
add_executable(qVariant src/qVariant.cpp)
target_link_libraries(qVariant PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(q_standard_item_model_q_model_index src/q_standard_item_model_q_model_index.cpp)
target_link_libraries(q_standard_item_model_q_model_index PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

add_executable(my_list_model src/my_list_model.cpp qml.qrc)
target_link_libraries(my_list_model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets)

if(EXISTS "src/sandbox.cpp")
    add_executable(sandbox src/sandbox.cpp )
    target_link_libraries(sandbox PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)
endif()

add_executable(reverse_string_proxy_model src/reverse_string_proxy_model.cpp)
target_link_libraries(reverse_string_proxy_model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

add_executable(q_sort_filter_proxy_model src/q_sort_filter_proxy_model.cpp)
target_link_libraries(q_sort_filter_proxy_model PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

add_executable(rowsInserted_rowsRemoved_dataChanged src/rowsInserted_rowsRemoved_dataChanged.cpp)
target_link_libraries(rowsInserted_rowsRemoved_dataChanged PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

add_executable(logging_category src/logging_category.cpp)
target_link_libraries(logging_category PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)

add_executable(environmental_variable_in_qt src/environmental_variable_in_qt.cpp)
target_link_libraries(environmental_variable_in_qt PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt5::Widgets Qt${QT_VERSION_MAJOR}::Concurrent)



