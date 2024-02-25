#include <QAbstractListModel>
#include <QtGui>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

struct DataItem {
  int ID;
  QString firstName;
};

/*

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

    // When implementing a table based model, rowCount() should return 0 when
    // the parent is valid.

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

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override {
    if (index.isValid() && role == Qt::EditRole) {
      DataItem &item = m_DataItems[index.row()];
      if (index.column() == 0)
        item.ID = value.toInt();
      else if (index.column() == 1)
        item.firstName = value.toString();
      qDebug() << "dataChanged:";

      emit dataChanged(index, index, {role});
      return true;
    }

    return false;
  }

  Qt::ItemFlags flags(const QModelIndex &index) const override {
    if (!index.isValid())
      return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  Q_INVOKABLE void addItem(int id, const QString &firstName) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_DataItems.append({id, firstName});
    endInsertRows();
  }

private:
  QVector<DataItem> m_DataItems;
};
*/

class MyListModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum MyRoles { IDRole = Qt::UserRole + 1, FirstNameRole };

  MyListModel(QObject *parent = nullptr) : QAbstractListModel(parent) {
    m_DataItems.append({10, "foo"});
    m_DataItems.append({11, "fee"});
    m_DataItems.append({12, "bar"});
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    if (parent.isValid())
      return 0;
    return m_DataItems.count();
  }

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

  Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value,
                           int role = Qt::EditRole) override {
    if (index.isValid() && role == Qt::EditRole) {
      DataItem &item = m_DataItems[index.row()];
      item.ID = value.toInt();
      emit dataChanged(index, index, {role});
      return true;
    }
    return false;
  }

  QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> roles;
    roles[IDRole] = "ID";
    roles[FirstNameRole] = "firstName";
    return roles;
  }

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

private:
  QVector<DataItem> m_DataItems;
};

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);

  int versionMajor = 1;
  int versionMinor = 0;

  // Register MyListModel with the QML type system
  qmlRegisterType<MyListModel>("com.example", 1, 0, "MyListModel");

  // QVariant value = myListModel.data(index, MyListModel::IDRole);

  QQmlApplicationEngine engine;

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

  // Expose the MyListModel object to QML
  engine.rootContext()->setContextProperty("myListModel", &myListModel);

  const QUrl url("qrc:/qml/my_list_model.qml");
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.load(url);
  return app.exec();
}

#include "my_list_model.moc"
