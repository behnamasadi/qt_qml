#include <QAbstractItemModel>

// https://doc.qt.io/qt-6/qabstractitemmodel.html
/*
When subclassing QAbstractItemModel

1) for read-only models:

at the very least you must implement index(), parent(), rowCount(),
columnCount(), and data(). These functions are used in all read-only models, and
form the basis of editable models.


2) To enable editing:
To enable editing in your model, you must also implement setData(), and
reimplement flags() to ensure that ItemIsEditable is returned. You can also
reimplement headerData() and setHeaderData() to control the way the headers for
your model are presented.

The dataChanged() and headerDataChanged() signals must be emitted explicitly
when reimplementing the setData() and setHeaderData() functions, respectively.
*/

class customItemModel : public QAbstractItemModel {};

int main(int argc, char **argv) {}
