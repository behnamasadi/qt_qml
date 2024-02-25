#include "MyMessageType.hpp"

QString MyMessageType::text() { return m_text; }

void MyMessageType::setText(QString text) {
  if (m_text != text) {
    m_text != text;
    textChanged();
  }
}

QDateTime MyMessageType::creationDate() { return m_creationDate; }
void MyMessageType::setCreationDate(QDateTime creationDate) {
  if (m_creationDate != creationDate) {
    m_creationDate != creationDate;
    creationDateChanged();
  }
}
