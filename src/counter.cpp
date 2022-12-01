#include "counter.hpp"

void Counter::setValue(int value) {
  if (value != m_value) {
    m_value = value;
    std::cout << "new value set!" << std::endl;
    // The emit line emits the signal valueChanged() from the object,
    emit valueChanged(value);
  }
}

void Counter::valueNotification() {
  std::cout << "Notification! " << m_value << std::endl;
}
