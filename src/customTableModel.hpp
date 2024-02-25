#include <QAbstractTableModel>
#include <QTime>
#include <QTimer>

class customTableModel : public QAbstractTableModel {

  Q_OBJECT
public:
  explicit customTableModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  void timerHit();
  QTimer *timer;

  /* When the view has to know what the cell's text is, it calls the method
   * MyModel::data(). */

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;

  /* setData() will be called each time the user edits a cell */
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
  void editCompleted(const QString &);
};
