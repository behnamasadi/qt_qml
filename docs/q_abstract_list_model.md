# QAbstractListModel
`QAbstractListModel` is a base class that provides an interface for implementing list models in Qt applications. It forms part of the Model/View architecture in Qt, which is used to separate data representation (model) from the user interface (view).


`QAbstractListModel` inherits from the `QAbstractItemModel` class and provides a simplified interface specifically tailored for list-based data models. It serves as a foundation for creating custom list models that can be used with various Qt view classes, such as `QListView`, `QTreeView`, and `QTableView`, to display and manipulate data.


To use `QAbstractListModel`, you typically subclass it and override its virtual functions to implement the behavior of the model. These functions include:

- **rowCount()**: Returns the number of rows (items) in the model.
- **data()**: Returns the data for a given index and role.
- **setData()**: Sets the data for a given index and role.
- **flags()**: Returns the item flags for a given index.
- **roleNames()**: Returns a mapping of role names to integer values.
- **index()**: Returns the model index for a given row and column.
- **parent()**: Returns the parent index of a given index.
- **insertRows()**: Inserts rows into the model.
- **removeRows()**: Removes rows from the model.

By implementing these functions appropriately, you define how the data is accessed and modified in your custom model. `QAbstractListModel` also provides signals, such as `dataChanged()`,  and `rowsInserted()`, that you can emit to notify the views about changes in the model data.

Example:

Let say you have the following data structure and you want to display them in table of ListView:
```cpp
struct DataItem {
  int ID;
  QString firstName;
};
```
you create a class that inherit from `QAbstractListModel`
 
```cpp
class MyListModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum MyRoles { IDRole = Qt::UserRole + 1, FirstNameRole };

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid() || index.row() >= m_DataItems.count())
      return QVariant();
    const DataItem &item = m_DataItems.at(index.row());
    switch (role) {
    case IDRole:
      return item.ID;
    case FirstNameRole:
      return item.firstName;
    default:
      return QVariant();
    }
  }
  
  QModelIndex index(int row, int column = 0,
                    const QModelIndex &parent = QModelIndex()) const override {
    if (hasIndex(row, column, parent)) {
      return createIndex(row, column);
    }
    return QModelIndex();
  }


  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[IDRole] = "ID";
    roles[FirstNameRole] = "firstName";
    return roles;
  }

private:
  QVector<DataItem> m_DataItems;
};
```

The `data(const QModelIndex &index, int role)` function in a subclass of `QAbstractListModel` is automatically called by the view (for example, a `ListView` in QML) to fetch data for display or for other roles. The `index` parameter specifies the index in the model for which to fetch data, and the `role` parameter specifies what kind of data to fetch.

In your QML `ListView`, when you use a role name in the delegate, like this:

```qml
Text {
    text: "ID: " + ID
}
```

the `ListView` automatically calls the `data` function with the `role` parameter set to the role corresponding to `"ID"`. The mapping from role names to role numbers is established by the `roleNames()` function in your model.

In your `MyListModel` class, you have defined the `roleNames()` function like this:

```cpp
QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[FirstNameRole] = "firstName";
    roles[IDRole] = "ID";
    return roles;
}
```

So when the `ListView` encounters `ID` in the delegate, it looks up the role number for `"ID"` (which is `MyRoles::IDRole`) and calls the `data` function with that role.

If you want to fetch data for a specific role in C++, you can call the `data` function directly, like this:

```cpp
QVariant value = myListModel.data(index, MyListModel::IDRole);
```

where `myListModel` is an instance of `MyListModel`, and `index` is a `QModelIndex` object specifying the index in the model for which to fetch data. The `MyListModel::IDRole` argument specifies that you want to fetch data for the `IDRole` role.


to modify the data you should implement the followings:

```cpp
Q_INVOKABLE bool
  insertRows(int row, int count,
             const QModelIndex &parent = QModelIndex()) override {
    if (row < 0 || row > m_DataItems.count())
      return false;
    beginInsertRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
      m_DataItems.insert(row, {0, ""});
    }
    endInsertRows();
    return true;
  }

  Q_INVOKABLE bool
  removeRows(int row, int count,
             const QModelIndex &parent = QModelIndex()) override {
    if (row < 0 || (row + count) > m_DataItems.count())
      return false;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
      m_DataItems.removeAt(row);
    }
    endRemoveRows();
    return true;
  }


  Q_INVOKABLE void addItem(int id, const QString &firstName) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_DataItems.append({id, firstName});
    endInsertRows();
  }
```

 
in C++ side:

```cpp
int versionMajor = 1;
int versionMinor = 0;

// Register MyListModel with the QML type system
qmlRegisterType<MyListModel>("com.example", 1, 0, "MyListModel");


MyListModel myListModel;

// Add some items to the model
myListModel.addItem(15, "item1");
myListModel.addItem(16, "item2");

// Example of calling setData
QModelIndex idx = myListModel.index(0); // get index for the first item
myListModel.setData(
idx, 999, MyListModel::IDRole); // set the ID of the first item to 999

// Example of calling insertRows
myListModel.insertRows(2, 1); // insert one row at position 2

// Example of calling removeRows
myListModel.removeRows(3, 1); // remove one row at position 3
```

in qml side:

```
    // Use the myListModel object as the model for the ListView
    ListView {
        anchors.fill: parent
        model: myListModel

    

    Component.onCompleted: {

        myListModel.addItem(1, "baz");
        myListModel.addItem(2, "qux");

            // Example of calling setData
            myListModel.setData(0, 30, MyListModel.IDRole); // set the ID of the first item to 30

            // Example of calling insertRows
            myListModel.insertRows(1, 1); // insert one row at position 1

            // Example of calling removeRows
            myListModel.removeRows(2, 1); // remove one row at position 2
    }

        // Define the delegate to display each item
        delegate: Item {
            width: parent.width
            height: 50

            Row {
                spacing: 10
                Text {
                    text: "ID: " + ID
                }
                Text {
                    text: "First Name: " + firstName
                }
            }
        }
    }
```   

 
 
 
 
 
 
 



[code](../src/q_list_view.cpp)
