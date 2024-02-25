#ifndef PIECHART_H
#define PIECHART_H

#include <QColor>
#include <QObject>
#include <QPainter>
#include <QPolygon>

/*
if we want to create a visual item that doesn't need to perform drawing
operations with the QPainter API, we can just subclass QQuickItem.
*/
#include <QtQuick/QQuickPaintedItem>

class PieChart : public QQuickPaintedItem {
  Q_OBJECT

  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
  explicit PieChart(QQuickItem *parent = nullptr);
  QString name() const;
  void setName(const QString &name);

  QColor color() const;
  Q_INVOKABLE void setColor(const QColor &color);

  void paint(QPainter *painter); // overrides QQuickPaintedItem::paint()

  Q_INVOKABLE void clearChart();

signals:
  void chartCleared();
  void colorChanged();

private:
  QString m_name;
  QColor m_color;
};

#endif // PIECHART_H
