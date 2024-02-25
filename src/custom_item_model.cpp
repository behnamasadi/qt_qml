#include <QAbstractItemModel>

//
/*
When subclassing QAbstractItemModel

1) for read-only models:

at the very least you must implement index(), parent(), rowCount(),
columnCount(), and data(). These functions are used in all read-only models, and
form the basis of editable models.


2) To enable editing:
To enable editing in your model, you must also implement setData(), and
reimplement flags() to ensure that ItemIsEditable is returned. You can also
reimplement headerData() and setHeaderData() to control the way the headers for
your model are presented.

The dataChanged() and headerDataChanged() signals must be emitted explicitly
when reimplementing the setData() and setHeaderData() functions, respectively.
*/

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeItem {
public:
  explicit TreeItem(const QString &name, TreeItem *parent = nullptr)
      : m_name(name), m_parent(parent) {}

  ~TreeItem() { qDeleteAll(m_children); }

  void appendChild(TreeItem *child) { m_children.append(child); }

  TreeItem *child(int row) { return m_children.value(row); }

  int childCount() const { return m_children.count(); }

  int columnCount() const {
    return 1; // We have only one column in this example
  }

  QVariant data(int column) const {
    if (column == 0)
      return m_name;

    return QVariant();
  }

  int row() const {
    if (m_parent)
      return m_parent->m_children.indexOf(const_cast<TreeItem *>(this));

    return 0;
  }

  TreeItem *parent() { return m_parent; }

private:
  QString m_name;
  QList<TreeItem *> m_children;
  TreeItem *m_parent;
};

class TreeModel : public QAbstractItemModel {
public:
  TreeModel(QObject *parent = nullptr) : QAbstractItemModel(parent) {
    m_rootItem = new TreeItem("Root");

    TreeItem *child1 = new TreeItem("Child 1", m_rootItem);
    TreeItem *child2 = new TreeItem("Child 2", m_rootItem);
    TreeItem *grandchild1 = new TreeItem("Grandchild 1", child2);

    m_rootItem->appendChild(child1);
    m_rootItem->appendChild(child2);
    child2->appendChild(grandchild1);
  }

  ~TreeModel() { delete m_rootItem; }

  QVariant data(const QModelIndex &index, int role) const override {
    if (!index.isValid())
      return QVariant();

    if (role != Qt::DisplayRole)
      return QVariant();

    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());

    return item->data(index.column());
  }

  Qt::ItemFlags flags(const QModelIndex &index) const override {
    if (!index.isValid())
      return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return "Name";

    return QVariant();
  }

  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override {
    if (!hasIndex(row, column, parent))
      return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
      parentItem = m_rootItem;
    else
      parentItem = static_cast<TreeItem *>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);

    if (childItem)
      return createIndex(row, column, childItem);
    else
      return QModelIndex();
  }

  QModelIndex parent(const QModelIndex &index) const override {
    if (!index.isValid())
      return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
      return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    TreeItem *parentItem;

    if (parent.column() > 0)
      return 0;

    if (!parent.isValid())
      parentItem = m_rootItem;
    else
      parentItem = static_cast<TreeItem *>(parent.internalPointer());

    return parentItem->childCount();
  }

  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    if (parent.isValid())
      return static_cast<TreeItem *>(parent.internalPointer())->columnCount();
    else
      return m_rootItem->columnCount();
  }

private:
  TreeItem *m_rootItem;
};

int main(int argc, char **argv) {}
