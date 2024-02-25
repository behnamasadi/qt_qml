#include "database.h"

// Database::Database()
//{

//}

Database::Database(QObject *parent) {}

Q_INVOKABLE Person Database::makePerson(const QString &name, int age) {
  return Person{};
}
Q_INVOKABLE Person Database::lookPerson(const QString &name) const {
  return Person{};
}
Q_INVOKABLE void Database::addPerson(const Person &person) {}
