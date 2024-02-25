#include <QAbstractListModel>
#include <QCoreApplication>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStringList>
#include <QStringListModel>
#include <algorithm>

class SortFilterStringProxyModel : public QSortFilterProxyModel {
  Q_OBJECT

public:
  SortFilterStringProxyModel(QObject *parent = nullptr)
      : QSortFilterProxyModel(parent) {}

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    QVariant originalData =
        QSortFilterProxyModel::sourceModel()->data(mapToSource(index), role);

    return originalData;
  }

protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex &sourceParent) const override {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(index).toString().contains("a");
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

  SortFilterStringProxyModel proxyModel;
  proxyModel.setSourceModel(&sourceModel);

  // Apply sorting, we're sorting based on column 0
  proxyModel.sort(0);

  // Now let's print out the  data from the proxy model
  for (int i = 0; i < proxyModel.rowCount(); i++) {
    QModelIndex proxyIndex = proxyModel.index(i, 0);
    qDebug() << proxyModel.data(proxyIndex).toString();
  }

  return app.exec();
}

#include "q_sort_filter_proxy_model.moc"