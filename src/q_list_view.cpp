#include <QtGui>
#include <QtQuick>

class Students : public QAbstractListModel {
  Q_OBJECT

public:
  Students() { mData.append(qMakePair(QStringLiteral("Guy"), 40)); }

  enum Roles { NameRole = Qt::UserRole, AgeRole };

  QVariant data(const QModelIndex &index, int role) const override {
    if (!index.isValid())
      return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
      qDebug() << "name role:" << mData.at(index.row()).first;
      return mData.at(index.row()).first;
    case AgeRole:
      return mData.at(index.row()).second;
    }

    return QVariant();
  }

  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override {
    switch (role) {
    case NameRole: {
      const QString newName = value.toString();
      mData[index.row()].first = value.toString();
      emit dataChanged(index, index, {NameRole});
      return true;
    }
    }

    return false;
  }

  /*
      For editable list models, you must also provide an implementation of
      setData(), and implement the flags() function so that it returns a value
      containing Qt::ItemIsEditable.

  */

  //  Qt::ItemFlags flags(const QModelIndex &index) const override {}

  int rowCount(const QModelIndex & /*parent*/ = QModelIndex()) const override {
    return mData.size();
  }

  virtual QHash<int, QByteArray> roleNames() const override {
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[AgeRole] = "age";
    return names;
  }

  Q_INVOKABLE void append() {
    preEntityAdded(0);
    mData.append(qMakePair(QStringLiteral("Guy"), 40));
    postEntityAdded();
  }

  Q_INVOKABLE void removeLast() {
    preEntityRemoved(0);
    mData.removeLast();
    postEntityRemoved();
  }

  Q_INVOKABLE void clear() {
    preEntitiesSet();
    mData.removeLast();
    postEntitiesSet();
  }

  /*
      Models that provide interfaces to resizable list-like data structures can
      provide implementations of insertRows() and removeRows().
  */

  //  QModelIndex index(int row, int column = 0,
  //                    const QModelIndex &parent = QModelIndex()) const
  //                    override {}

protected:
  void preEntityAdded(int index) {
    qDebug() << objectName() << "preEntityAdded at index" << index;
    beginInsertRows(QModelIndex(), index, index);
  }

  void postEntityAdded() {
    qDebug() << objectName() << "postEntityAdded";
    endInsertRows();
  }

  void preEntityRemoved(int index) {
    qDebug() << objectName() << "preEntityRemoved index" << index
             << "rowCount() is" << rowCount();
    beginRemoveRows(QModelIndex(), index, index);
  }

  void postEntityRemoved() {
    qDebug() << objectName() << "postEntityRemoved";
    endRemoveRows();
  }

  void preEntitiesSet() {
    qDebug() << objectName()
             << "about to call beginResetModel() - rowCount() is" << rowCount();
    beginResetModel();
    qDebug() << objectName() << "called beginResetModel()";
  }

  void postEntitiesSet() {
    qDebug() << objectName() << "about to call endResetModel() - rowCount() is"
             << rowCount();
    endResetModel();
    qDebug() << objectName() << "called endResetModel()";
  }

private:
  QVector<QPair<QString, int>> mData;
};

int main(int argc, char **argv) {

  QGuiApplication app(argc, argv);

  int versionMajor = 1;
  int versionMinor = 0;

  qmlRegisterType<Students>("com.mycompany.qmlcomponents", versionMajor,
                            versionMinor, "Students");

  QQmlApplicationEngine engine;
  const QUrl url("qrc:/qml/q_list_view.qml");
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

#include "q_list_view.moc"
