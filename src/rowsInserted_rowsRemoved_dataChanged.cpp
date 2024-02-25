#include <QAbstractListModel>
#include <QCoreApplication>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStringList>
#include <QStringListModel>
#include <algorithm>

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
#include "rowsInserted_rowsRemoved_dataChanged.moc"
