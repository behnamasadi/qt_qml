# Model/View

Model/View is a technology used to separate data from views. Qt Quick has the notion of models, views, and delegates to display data.  

1. Model: contains the data and its structure. Qt provides several built-in models, such as `ListModel`, `XmlListModel`, and `JsonListModel`. Additionally, you can create custom models by subclassing `QAbstractListModel` or `QAbstractTableModel` in C++ and exposing them to QML.

2. View: a container that displays the data. The view might display the data in a list or a grid.

- ListView: arranges items in a horizontal or vertical list
- GridView: arranges items in a grid within the available space
- PathView: arranges items on a path
- TableView: arranges data from a `QAbstractTableModel` in a table
- TreeView: arranges data from a `QAbstractItemModel` in a tree

3. Delegate: Dictates how the data should appear in the view and what sort of behavior should have. QML provides delegates in the form of DelegateModel, which allows you to specify custom delegates for different roles or conditions..

A developer can swap a list view with a grid view with little changes to the data.

## Roles

Each item in the model can have multiple roles associated with it, such as `Qt::DisplayRole`, `Qt::EditRole`, and `Qt::ToolTipRole`, which define different aspects of the data to be displayed or edited.

Here's an example of how you might use Qt::DisplayRole to provide display data for a custom model:

```cpp
class MyModel : public QAbstractItemModel {
    // ...

    // Implementation of data() function
    QVariant data(const QModelIndex& index, int role) const override {
        if (role == Qt::DisplayRole) {
            // Retrieve data for the display role
            // Assuming the model stores QString data
            QString itemData = getItemData(index);

            return itemData;
        }

        // For other roles, delegate to the base class implementation
        return QAbstractItemModel::data(index, role);
    }

    // ...
};
```

In the above example, the data() function is overridden to provide data for different roles requested by the view. When the role parameter matches `Qt::DisplayRole`, the function retrieves the relevant data for the item and returns it as a QVariant. The view will then use this data to display the item in an appropriate manner, such as in a table cell or a list item.

It's important to note that the `data()` function can be called with different roles, and you can customize the behavior based on the specific role requested. In this example, we handle `Qt::DisplayRole` specifically, but you can handle other roles like `Qt::ToolTipRole`, `Qt::DecorationRole`, or any custom roles you define.

By implementing the `data()` function in your custom model, you can control the data that is displayed by views using `Qt::DisplayRole` and other roles to provide appropriate information for the specific use cases in your application.

## ItemFlags

`Qt::ItemFlags` is an enumeration in the Qt framework that represents various properties and permissions for an item in a model. It is commonly used in the `flags()` function of a custom model to specify the capabilities of each item in the model.

Here's an example of how you might use `Qt::ItemFlags` to define the flags for items in a custom model:

For editable list models, you must also provide an implementation of
setData(), and implement the flags() function so that it returns a value
containing Qt::ItemIsEditable.

```cpp
// Custom model class derived from QAbstractItemModel
class MyModel : public QAbstractItemModel {
    // ...

    // Implementation of flags() function
    Qt::ItemFlags flags(const QModelIndex& index) const override {
        Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

        // Add specific flags based on the item's position or data
        if (index.isValid()) {
            // Set the item as editable and selectable
            return defaultFlags | Qt::ItemIsEditable | Qt::ItemIsSelectable;
        }

        // For invalid indexes, return the default flags
        return defaultFlags;
    }

    // ...
};
```

In the above example, the flags() function is overridden to define the item flags for each item in the model. The function takes a QModelIndex parameter, which represents the index of the item for which flags are being queried.

In this implementation, we start by obtaining the default flags from the base class using QAbstractItemModel::flags(index). Then, based on the specific conditions, we modify or add flags to the default flags.

In the example, we check if the index is valid. If it is, we add the Qt::ItemIsEditable and Qt::ItemIsSelectable flags to allow the item to be edited and selected by the view. If the index is invalid, we return the default flags without any modifications.

By customizing the flags() function in your custom model, you can control the item's behavior in views. The flags you set determine whether the item can be edited, selected, dragged, dropped, and more, providing fine-grained control over the user interaction with the model's items.

Refs: [1](https://doc.qt.io/qt-6/qtquick-modelviewsdata-modelview.html), [2](https://stackoverflow.com/questions/27400025/using-qabstractlistmodel-in-listview)
