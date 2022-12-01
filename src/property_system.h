#ifndef PROPERTY_SYSTEM_H
#define PROPERTY_SYSTEM_H

#include <QObject>

class property_system : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };

    explicit property_system(QObject *parent = nullptr);


    void setPriority(Priority priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const
    { return m_priority; }



signals:
    void priorityChanged(Priority);
private:
    Priority m_priority;
};

#endif // PROPERTY_SYSTEM_H
