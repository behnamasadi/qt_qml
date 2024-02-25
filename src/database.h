#ifndef DATABASE_H
#define DATABASE_H

#include "person.h"
#include <QHash>
#include <QObject>

class Database : public QObject {
  Q_OBJECT
public:
  explicit Database(QObject *parent = nullptr);
  Q_INVOKABLE Person makePerson(const QString &name, int age);
  Q_INVOKABLE Person lookPerson(const QString &name) const;
  Q_INVOKABLE void addPerson(const Person &person);

  // Database();
  QHash<QString, Person> m_persons;
};

#endif // DATABASE_H
