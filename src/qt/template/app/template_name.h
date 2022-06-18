#pragma once

#include <QWidget>

class TemplateName : public QWidget {
  Q_OBJECT

 public:
  explicit TemplateName(QWidget* parent = nullptr) : QWidget(parent) { initUi(); }

  void setBkColor(const QString& color);

 private:
  void initUi();

  QString mBkColor{"cornsilk"};
};
