#include "customTableModel.hpp"
#include <QBrush>
#include <QDebug>
#include <QFont>

customTableModel::customTableModel(QObject *parent)
    : QAbstractTableModel(parent), timer(new QTimer(this)) {
  timer->setInterval(1000);
  connect(timer, &QTimer::timeout, this, &customTableModel::timerHit);
  timer->start();
}

int customTableModel::rowCount(const QModelIndex &parent) const { return 2; }
int customTableModel::columnCount(const QModelIndex &parent) const { return 3; }

/*
Each item in the model has a set of data elements associated with it, each with
its own role. The roles are used by the view to indicate to the model which type
of data it needs

Qt::DisplayRole
Qt::EditRole
Qt::ToolTipRole

*/

QVariant customTableModel::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int col = index.column();
  // generate a log message when this method gets called
  // qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

  switch (role) {
  case Qt::DisplayRole:
    //    if (row == 0 && col == 1)
    //      return QString("<--left");
    //    if (row == 1 && col == 1)
    //      return QString("right-->");

    //    return QString("Row%1, Column%2").arg(row + 1).arg(col + 1);

    return QTime::currentTime().toString();
  case Qt::FontRole:
    if (row == 0 && col == 0) { // change font only for cell(0,0)
      QFont boldFont;
      boldFont.setBold(true);
      return boldFont;
    }
    break;
  case Qt::BackgroundRole:
    if (row == 1 && col == 2) // change background only for cell(1,2)
      return QBrush(Qt::red);
    break;
  case Qt::TextAlignmentRole:
    if (row == 1 && col == 1) // change text alignment only for cell(1,1)
      return int(Qt::AlignRight | Qt::AlignVCenter);
    break;
  case Qt::CheckStateRole:
    if (row == 1 && col == 0) // add a checkbox to cell(1,0)
      return Qt::Checked;
    break;
  }
  return QVariant();
}

void customTableModel::timerHit() {
  // we identify the top left cell
  int row, column;

  row = 0;
  column = 0;
  QModelIndex topLeft = createIndex(row, column);

  row = 0;
  column = 0;
  QModelIndex bottomRight = createIndex(row, column);
  // emit a signal to make the view reread identified data
  // emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
  emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
}

QVariant customTableModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    switch (section) {
    case 0:
      return QString("first");
    case 1:
      return QString("second");
    case 2:
      return QString("third");
    }
  }
  return QVariant();
}

bool customTableModel::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  qDebug() << QString("setData: row %1, col%2, role %3")
                  .arg(index.row())
                  .arg(index.column())
                  .arg(role);

  if (role == Qt::EditRole) {
    if (!checkIndex(index))
      return false;
    //        //save value from editor to member m_gridData
    //        m_gridData[index.row()][index.column()] = value.toString();
    //        //for presentation purposes only: build and emit a joined string
    //        QString result;
    //        for (int row = 0; row < ROWS; row++) {
    //            for (int col= 0; col < COLS; col++)
    //                result += m_gridData[row][col] + ' ';
    //        }

    QString result = "finito";
    emit editCompleted(result);
    return true;
  }
  return false;
}

Qt::ItemFlags customTableModel::flags(const QModelIndex &index) const {
  return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
