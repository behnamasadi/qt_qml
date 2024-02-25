#include "piechart.h"

PieChart::PieChart(QQuickItem *parent) : QQuickPaintedItem(parent) {}

QString PieChart::name() const { return m_name; }

void PieChart::setName(const QString &name) {}

QColor PieChart::color() const { return m_color; }

void PieChart::setColor(const QColor &color) {
  if (m_color != color) {
    m_color = color;
    update(); // repaint with the new color
    emit colorChanged();
  }
}

void PieChart::paint(QPainter *painter) {
  QPen pen(m_color, 2);
  painter->setPen(pen);
  painter->setRenderHints(QPainter::Antialiasing, true);
  painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
  QPolygon qpolygon;

  qpolygon.append(QPoint(20, 3));
  qpolygon.append(QPoint(8, 9));
  qpolygon.append(QPoint(45, 30));
  qpolygon.append(QPoint(15, 50));
  painter->drawPoints(qpolygon);
}

void PieChart::clearChart() {
  setColor(QColor(Qt::transparent));
  update();

  emit chartCleared();
}
