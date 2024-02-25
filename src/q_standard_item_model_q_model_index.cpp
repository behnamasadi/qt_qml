#include <QDebug>
#include <QStandardItemModel>

int main() {

  int rows = 3;
  int cols = 2;
  QStandardItemModel dataModel(rows, cols);

  QObject::connect(
      &dataModel, &QStandardItemModel::itemChanged, [=](QStandardItem *item) {
        qDebug() << "item on row: " << item->row() << ","
                 << "col: " << item->column() << " has changed";
        qDebug() << "item->index().data():" << item->index().data();
        qDebug() << "item->text():" << item->text();
      });

  for (int r = 0; r < dataModel.rowCount(); r++) {
    for (int c = 0; c < dataModel.columnCount(); c++) {
      QModelIndex index = dataModel.index(r, c);
      dataModel.setData(index, QString("%1,%2").arg(r).arg(c));
    }
  }

  QStandardItem *item1 =
      new QStandardItem(QString("row %0, column %1").arg(4).arg(0));
  QStandardItem *item2 =
      new QStandardItem(QString("row %0, column %1").arg(4).arg(1));

  dataModel.setItem(3, 0, item1);
  dataModel.setItem(3, 1, item2);

  for (int r = 0; r < dataModel.rowCount(); r++) {
    for (int c = 0; c < dataModel.columnCount(); c++) {
      QModelIndex index = dataModel.index(r, c);

      QVariant foo = dataModel.data(index);
      qDebug() << foo.toString();
    }
  }
  dataModel.item(3, 1)->setText("foo");
}
