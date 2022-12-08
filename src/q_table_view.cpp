#include "customTableModel.hpp"
#include <QApplication>
#include <QHeaderView>
#include <QTableView>

// https://doc.qt.io/qt-6/modelview.html

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QTableView tableView;
  customTableModel *customTable = new customTableModel();

  tableView.setModel(customTable);
  // tableView.verticalHeader()->hide();
  tableView.show();

  return app.exec();
}
