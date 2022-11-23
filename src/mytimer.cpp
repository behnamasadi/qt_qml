#include "mytimer.h"
#include <QDebug>
#include <QColor>

mytimer::mytimer(QObject *parent) : QObject(parent)
{
    QTimer *timer=new QTimer(this);
    connect(timer, &QTimer::timeout,this, &mytimer::addOneSecond);
    timer->start(1000);

    QVariant var=QVariant::fromValue(QColor(Qt::red));
    QColor col= var.value<QColor>();

}

void mytimer::addOneSecond()
{
    qDebug()<<QString::fromStdString( ( "foo") );
    //std::cout<< <<std::endl;
}
