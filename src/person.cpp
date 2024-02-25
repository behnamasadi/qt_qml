#include "person.h"

Person::Person() {}

Q_INVOKABLE QString Person::toString() const { return QString{}; }

Person::Person(const QString &name, int age) {}
