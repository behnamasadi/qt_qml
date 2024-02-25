# QAbstractItemModel
`QAbstractItemModel` is the base class that provides an interface for implementing hierarchical data models. It forms a key component of the Model/View architecture in Qt, which separates the data representation (model) from the user interface (view).

`QAbstractItemModel` defines a set of functions and signals that need to be implemented or overridden by derived classes to create custom data models. These models can then be used with various Qt view classes, such as `QTreeView`, `QListView`, and `QTableView`, to display and manipulate hierarchical data. It defines functions such as:

1. `rowCount()`: Returns the number of rows (items) in a model or under a specific parent index.
2. `columnCount()`: Returns the number of columns in a model or under a specific parent index.
3. `data()`: Returns the data for a given model index and role.
4. `setData()`: Sets the data for a given model index and role.
5. `flags()`: Returns the item flags for a given model index.
6. `roleNames():` Returns a mapping of role names to integer values.
7. `index()`: Returns the model index for a given row, column, and parent index.
8. `parent()`: Returns the parent index of a given model index.
9. `headerData()`: Returns the header data for a given section, orientation, and role.

By implementing or overriding these functions, you define how the data is accessed and manipulated in your custom model.
`QAbstractItemModel` also provides various signals, such as `dataChanged()`, `layoutChanged()`, and `modelReset()`.


Additionally, it supports features like drag-and-drop operations, item selection, and sorting/filtering of data. It allows customization of the item appearance, editability, and more through item delegates.


1) for read-only models:

at the very least you must implement `index()`, `parent()`, `rowCount()`,
`columnCount()`, and `data()`. These functions are used in all read-only models, and
form the basis of editable models.


2) To enable editing:
To enable editing in your model, you must also implement `setData()`, and
reimplement `flags()` to ensure that `ItemIsEditable` is returned. You can also
reimplement `headerData()` and `setHeaderData()` to control the way the headers for
your model are presented.

The `dataChanged()` and `headerDataChanged()` signals must be emitted explicitly
when `reimplementing` the `setData()` and `setHeaderData()` functions, respectively.


In this example, we create a custom model called TreeModel by subclassing QAbstractItemModel. The model represents a simple tree structure where each item has a name and can have child items. The root item is represented by a TreeItem called "Root".

The TreeModel class overrides several virtual functions of QAbstractItemModel, such as data(), flags(), headerData(), index(), parent(), rowCount(), and columnCount(), to define the behavior of the model.

The TreeModel uses the TreeItem class to represent the actual data and structure of the model. The TreeItem class holds the name and parent-child relationships between items. It also provides functions to access and manipulate the data.

This example demonstrates a simple implementation of QAbstractItemModel for a tree structure. The model can be used with appropriate Qt view classes, such as QTreeView, to display and interact with the hierarchical data.

Refs: [1](https://doc.qt.io/qt-6/qabstractitemmodel.html)


[code](src/custom_item_model.cpp)
