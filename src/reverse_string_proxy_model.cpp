#include <QAbstractListModel>
#include <QAbstractProxyModel>
#include <QCoreApplication>
#include <QLoggingCategory>
#include <QStringList>
#include <QStringListModel>

class ReverseStringProxyModel : public QAbstractProxyModel {
  Q_OBJECT
public:
  ReverseStringProxyModel(QObject *parent = nullptr)
      : QAbstractProxyModel(parent) {}

  // Map index from source model to proxy model

  QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override {
    return index(sourceIndex.row(), sourceIndex.column());
  }
  // Map index from proxy model to source model

  QModelIndex mapToSource(const QModelIndex &proxyIndex) const override {
    // sourceModel is of type QAbstractItemModel and comes from
    return sourceModel()->index(proxyIndex.row(), proxyIndex.column());
  }

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    QVariant originalData =
        QAbstractProxyModel::sourceModel()->data(mapToSource(index), role);
    QString reversedString = originalData.toString();
    std::reverse(reversedString.begin(), reversedString.end());
    return reversedString;
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return sourceModel()->rowCount(parent);
  }

  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    return sourceModel()->columnCount(parent);
  }

  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override {
    Q_UNUSED(parent);
    return createIndex(row, column);
  }

  QModelIndex parent(const QModelIndex &child) const override {
    Q_UNUSED(child);
    return QModelIndex();
  }
};

int main(int argc, char **argv) {

  QCoreApplication app(argc, argv);

  QStringListModel sourceModel;
  sourceModel.setStringList(QStringList() << "apple"
                                          << "banana"
                                          << "cherry");

  ReverseStringProxyModel proxyModel;
  proxyModel.setSourceModel(&sourceModel);

  // Now let's print out the reversed data from the proxy model
  for (int i = 0; i < proxyModel.rowCount(); i++) {
    QModelIndex proxyIndex =
        proxyModel.index(i, 0); // Assuming a list, so column is always 0
    qDebug() << proxyModel.data(proxyIndex).toString();
  }

  qDebug() << sourceModel.data(sourceModel.index(0, 0)).toString();

  return app.exec();
}

#include "reverse_string_proxy_model.moc"