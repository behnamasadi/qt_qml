#include "counter.hpp"

int main() {
  Counter a, b;
  QObject::connect(&a, &Counter::valueChanged, &b, &Counter::setValue);

  a.setValue(2);
  std::cout << b.value() << std::endl;
}
