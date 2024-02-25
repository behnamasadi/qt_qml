#ifndef USER_H
#define USER_H

#include <QDate>
#include <QObject>

class User : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged)
  Q_PROPERTY(Role role READ getRole WRITE setRole NOTIFY roleChanged)

  Q_INVOKABLE void showMessageToUSer() {}

public:
  // explicit User(QObject *parent = nullptr);
  enum Role { Dev, Manager, Tester, Fullstack };
  Q_ENUM(Role);
  User(const QString &name, int age, Role role, QObject *parent = nullptr);

  QString getName() const;
  void setName(const QString &name);

  int getAge() const;
  void setAge(int age);
  void setRole(Role role);
  Role getRole();

signals:
  void nameChanged();
  void ageChanged();
  void roleChanged();

public slots:
  void changeRole();

private:
  int m_age;
  QString m_name;
  QDate m_birthdate;
  Role m_role;
};

#endif // USER_H
