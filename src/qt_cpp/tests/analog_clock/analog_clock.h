#pragma once

#include <QWidget>

class AnalogClock : public QWidget {
  Q_OBJECT
 public:
  explicit AnalogClock(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private slots:
  void Update();
};
