#include "user.h"

// User::User(QObject *parent) : QObject{parent}
//{

//}

User::User(const QString &name, int age, Role role, QObject *parent)
    : m_name(name), m_age(age), m_role(role) {}

QString User::getName() const { return m_name; }
void User::setName(const QString &name) {
  if (name == m_name)
    return;
  m_name = name;
  emit nameChanged();
}

int User::getAge() const { return m_age; }
void User::setAge(int age) {
  if (age == m_age)
    return;
  m_age = age;
  emit ageChanged();
}

User::Role User::getRole() { return m_role; }
void User::setRole(Role role) {
  if (m_role == role)
    return;
  m_role = role;
  emit roleChanged();
}

void User::changeRole() {
  setRole(m_role == User::Dev ? User::Manager : User::Dev);
}
