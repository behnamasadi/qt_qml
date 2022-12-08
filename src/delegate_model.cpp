#include <QStyledItemDelegate>

/*
Writing custom delegates is the right choice if you want to show your data with
a custom graphical representation inside the grid of the view class. If you want
to leave the grid, you would not use a custom delegate but a custom view class.

*/

class StarDelegate : public QStyledItemDelegate {
  // Q_OBJECT
  StarDelegate(QWidget *parent = nullptr);

  /*

  paint() draws stars depending on the content of the underlying data. The data
  can be looked up by calling index.data().

  */

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;

  /*

  The delegate's sizeHint() method is used to obtain each star's dimensions, so
  the cell will provide enough height and width to accommodate the stars.
  */

  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const;
};

int main(int argc, char **argv) {}
