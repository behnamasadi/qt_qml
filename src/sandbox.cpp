#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cmath>
#include <iomanip>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>


template <typename T>
void printArray(T array)
{
    for (const auto &element:array)
        std::cout<< element <<std::endl;
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    // both of them work:
    view.setSource(QUrl("qrc:/qml/list_view.qml"));
    // view.setSource(QUrl::fromLocalFile("qml/simple_quickview.qml"));

    view.show();
    return app.exec();
    
    /*
    
    onTriggered
https://doc.qt.io/qt-6/qtquickhandlers-index.html
QCoreApplication::sendEvent or QCoreApplication::postEvent
    */
    
}




