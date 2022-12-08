#include <QAbstractListModel>
#include <QGuiApplication>
#include <memory>

// https://doc.qt.io/qt-5/qabstractlistmodel.html

/* model represents a one-dimensional structure */

/*
When subclassing QAbstractListModel, you must provide implementations of the
rowCount() and data() functions. Well behaved models also provide a headerData()
implementation.
*/

class students : public QAbstractListModel {
  // Q_OBJECT

  students(QObject *parent = nullptr) {}

  Q_INVOKABLE virtual int
    /*
Returns the number of rows under the given parent. When the parent is
valid it means that rowCount is returning the number of children of parent.
*/

    rowCount(const QModelIndex &parent = QModelIndex()) const override {

    return 0;
  }

  /*columnCount() function is implemented for interoperability with all kinds of
   * views, but by default informs views that the model contains only one
   * column.*/

  /*
If your model is used within QML and requires roles other than the default
ones provided by the roleNames() function, you must override it.
*/

  /*
For editable list models, you must also provide an implementation of
setData(), and implement the flags() function so that it returns a value
containing Qt::ItemIsEditable.

  */

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override {}

  Qt::ItemFlags flags(const QModelIndex &index) const override {}

  /*
Models that provide interfaces to resizable list-like data structures can
provide implementations of insertRows() and removeRows().
*/

  QModelIndex index(int row, int column = 0,
                    const QModelIndex &parent = QModelIndex()) const override {}
};

int main(int argc, char **argv) {}
