# 1. ListView

A `ListView` displays data from models created from built-in QML types like `ListModel` and `XmlListModel`, or custom model classes defined in C++ that inherit from `QAbstractItemModel` or `QAbstractListModel`.

## 1.2. ListView Displaying ListModel

```
ListModel {
    id: contact_list
    ListElement {
        first_name: "Foo"
        last_name: " Wise"
        phone: 1111
    }
    ListElement {
        first_name: "Fee"
        last_name: "Smith"
        phone: 2222
    }
    ListElement {
        first_name: "Bar"
        last_name: "Brown"
        phone: 3333
    }
}

ListView
{
    id: my_contact_list_view
    anchors.fill: parent
    model: contact_list
    delegate: Text {  text: first_name + ", " + last_name}
}
```

An improved list view:

```
    Component
    {
        id:contactDelegate
        Item
        { width: 200; height: 20
            Column{
                Text{text: first_name+ ","+last_name}
            }
        }

    }

    ListView
    {
        id: my_contact_list_view
        anchors.fill: parent
        model: contact_list
        delegate: contactDelegate
    }
```

code [1](../qml/list_view.qml), [2](../src/list_view.cpp)

## 1.3. ListView Displaying QAbstractItemModel

To implement a simple read-only model, we only need to implement the `rowCount()` function to return the number of items in the list, and the `data()` function to retrieve items from the list.

Example of read only:

```cpp
struct DataItem {
  int ID;
  QString firstName;
};

class MyListModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum MyRoles { IDRole = Qt::UserRole + 1, FirstNameRole };

  MyListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {

    m_DataItems.append({10, "foo"});
    m_DataItems.append({11, "fee"});
    m_DataItems.append({12, "bar"});
  }



  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    /* If you do not have a value to return, return an invalid
     * (default-constructed) QVariant. */

    if (!index.isValid() || index.row() > m_DataItems.count())
      return QVariant();

    const DataItem item = m_DataItems.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
      qDebug() << "DisplayRole";
    case MyRoles::IDRole:
      qDebug() << "ID role:" << item.ID;

      return item.ID;
    case MyRoles::FirstNameRole:
      qDebug() << "FirstName role:" << item.firstName;
      return item.firstName;
    default:
      break;
    }
    return QVariant();
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    /*
      When implementing a table based model, rowCount() should return 0 when the
      parent is valid.
    */
    if (parent.isValid())
      return 0;
    return m_DataItems.count();
  }

  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[FirstNameRole] = "firstName";
    roles[IDRole] = "ID";
    return roles;
  }

private:
  QVector<DataItem> m_DataItems;
};
```

In your main:

```cpp
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  MyListModel myListModel;
  engine.rootContext()->setContextProperty("_myListModel", &myListModel);

  const QUrl url(QStringLiteral("qrc:/qml/my_list_model.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
```
  
In the qml side:

```
    ListView {
        width: parent.width
        height: parent.height
        model: _myListModel
        delegate: Item {
            width: parent.width
            height: 30
            Column {
                Text {
                    text: "First Name: " + model.firstName
                    font.bold: true
                }
                Text {
                    text: "ID: " + model.ID
                }
            }
        }
    }
```

code: [1](../src/q_list_view.cpp), [2](../qml/q_list_view.qml)

Refs: [1](https://gist.github.com/mitchcurtis/3fbaafb8ed1717fb76bc)
