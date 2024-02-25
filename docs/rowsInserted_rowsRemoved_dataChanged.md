# ListModel Signals
Let's start by understanding the purpose of these signals:

1. **`rowsInserted`**: This signal is emitted by a model after rows have been inserted.
2. **`rowsRemoved`**: Emitted by the model after rows have been removed.
3. **`dataChanged`**: Emitted when the data stored under a particular model index is modified.

To demonstrate, let's slightly expand our example:

1. We will connect to these signals from the source model (`QStringListModel`).
2. For demonstration purposes, after setting the initial string list, we'll modify the source model to trigger these signals.

Here's an expanded version of our previous example:

```cpp

class StringProxyModel : public QSortFilterProxyModel {
  Q_OBJECT

public:
  StringProxyModel(QObject *parent = nullptr) : QSortFilterProxyModel(parent) {}

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    QVariant originalData =
        QSortFilterProxyModel::sourceModel()->data(mapToSource(index), role);

    return originalData;
  }
};

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  QStringListModel sourceModel;
  sourceModel.setStringList(QStringList() << "apple"
                                          << "berry"
                                          << "cherry"
                                          << "date"
                                          << "fig");

  QObject::connect(&sourceModel, &QStringListModel::rowsInserted,
                   [](const QModelIndex &parent, int first, int last) {
                     Q_UNUSED(parent);
                     qDebug() << "Rows inserted from" << first << "to" << last;
                   });

  QObject::connect(&sourceModel, &QStringListModel::rowsRemoved,
                   [](const QModelIndex &parent, int first, int last) {
                     Q_UNUSED(parent);
                     qDebug() << "Rows removed from" << first << "to" << last;
                   });

  QObject::connect(
      &sourceModel, &QStringListModel::dataChanged,
      [](const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        qDebug() << "Data changed from" << topLeft.row() << "to"
                 << bottomRight.row();
      });

  StringProxyModel proxyModel;
  proxyModel.setSourceModel(&sourceModel);

  qDebug() << "-----------------sourceModel------------------";

  // Modify source model to trigger signals
  sourceModel.removeRow(1); // Removing "berry", triggers rowsRemoved
  sourceModel.setData(
      sourceModel.index(0, 0),
      "mango"); // Changing "apple" to "mango", triggers dataChanged
  sourceModel.insertRows(
      3, 2); // Inserting 2 rows at position 3, triggers rowsInserted

  qDebug() << "-----------------proxyModel------------------";

  // Now let's print out the reversed data from the proxy model
  for (int i = 0; i < proxyModel.rowCount(); i++) {
    QModelIndex proxyIndex = proxyModel.index(i, 0);
    qDebug() << proxyModel.data(proxyIndex).toString();
  }

  return app.exec();
}
```

In the above example, after setting up the initial data, we perform some modifications:

1. Removing the row containing "berry".
2. Changing "apple" to "mango".
3. Inserting two new rows.

These actions will trigger the `rowsRemoved`, `dataChanged`, and `rowsInserted` signals, respectively. The connections we set up will log these events using `qDebug()`.



[code](../src/rowsInserted_rowsRemoved_dataChanged.cpp)
