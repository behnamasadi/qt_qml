#include <QObject>

class message : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged);

  /*
  The parent of an object may be viewed as the object's owner. For instance, a
  dialog box is the parent of the OK and Cancel buttons it contains.

  The destructor of a parent object destroys all child objects.

  Setting parent to nullptr constructs an object with no parent. If the object
  is a widget, it will become a top-level window.
  */

public:
  message(QObject *parent) : QObject(parent) {}
  message() {}
  QString author() { return m_author; }
  void setAuthor(QString author) {
    if (m_author != author) {
      m_author = author;
      emit authorChanged();
    }
  }

public slots:
signals:
  void authorChanged();

private:
  QString m_author;
};
