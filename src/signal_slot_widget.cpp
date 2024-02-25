#include <QApplication>
#include <QWidget>
#include <QtWidgets/QtWidgets>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QWidget *window = new QWidget();

  QSlider *slider = new QSlider(Qt::Horizontal);
  QSpinBox *spinbox = new QSpinBox();

  QObject::connect(slider, &QSlider::valueChanged, spinbox,
                   &QSpinBox::setValue);

  auto layout = new QVBoxLayout(window);
  layout->addWidget(slider);
  layout->addWidget(spinbox);

  window->show();
  app.exec();
}
