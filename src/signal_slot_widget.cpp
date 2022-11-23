#include <QWidget>
#include <QApplication>
#include <QtWidgets/QtWidgets>
#include "mytimer.h"


int main(int argc , char * argv[])
{
    QApplication app( argc, argv );
    QWidget *window=new QWidget();


    QSlider *slider=new QSlider(Qt::Horizontal);
    QSpinBox *spinbox=new QSpinBox();

    QObject::connect(slider,&QSlider::valueChanged,spinbox, &QSpinBox::setValue);
    //QObject::connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(steValue(int)) );


    auto layout = new QVBoxLayout(window);
    layout->addWidget(slider);
    layout->addWidget(spinbox);

    //call your slot what it does and not when its called

    mytimer mytimer_obj;

    window->show();
    app.exec();


}
