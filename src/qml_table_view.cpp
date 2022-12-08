#include <QGuiApplication>
// https://doc.qt.io/qt-5/qml-qtquick-tableview.html

/*

A TableView has a model that defines the data to be displayed, and a delegate
that defines how the data should be displayed.


A TableView displays data from models created from built-in QML types such as
1) ListModel and
2) XmlListModel,
which populates the first column only in a TableView. To create models with
multiple columns, either use TableModel or a C++ model that inherits
QAbstractItemModel.


When subclassing QAbstractItemModel, at the very least you must implement
index(), parent(), rowCount(), columnCount(), and data(). These functions are
used in all read-only models, and form the basis of editable models.
*/

int main(int argc, char **argv) {}
