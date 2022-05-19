#include "analog_clock.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

AnalogClock::AnalogClock(QWidget* parent /* = nullptr*/) : QWidget(parent) {
  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &AnalogClock::Update);
  timer->start(1000);

  setWindowTitle("Analog Clock");
  setAttribute(Qt::WA_DeleteOnClose);
  setMinimumSize(800, 600);
}

void AnalogClock::paintEvent(QPaintEvent* event) {
  constexpr const QPoint hour_hand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40)};
  constexpr const QPoint minute_hand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70)};
  constexpr const QPoint second_hand[3] = {QPoint(3, 8), QPoint(-3, 8), QPoint(0, -80)};

  constexpr const QColor hour_color(127, 0, 127);
  constexpr const QColor minute_color(0, 127, 127, 191);
  constexpr const QColor second_color(255, 0, 0, 255);

  int side = qMin(width(), height());
  QTime time = QTime::currentTime();

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);

  painter.setPen(Qt::NoPen);
  painter.setBrush(hour_color);

  painter.save();
  painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
  painter.drawConvexPolygon(hour_hand, 3);
  painter.restore();

  painter.setPen(hour_color);
  for (int i = 0; i < 12; ++i) {
    painter.drawLine(88, 0, 96, 0);
    painter.rotate(30);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(minute_color);

  painter.save();
  painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
  painter.drawConvexPolygon(minute_hand, 3);
  painter.restore();

  painter.setPen(minute_color);
  for (int j = 0; j < 60; ++j) {
    if ((j % 5) != 0) {
      painter.drawLine(92, 0, 96, 0);
    }
    painter.rotate(6.0);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(second_color);

  painter.save();
  painter.rotate(6.0 * (time.second()));
  painter.drawConvexPolygon(second_hand, 3);
  painter.restore();
}

void AnalogClock::Update() { update(); }
