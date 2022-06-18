#include "template_name.h"

void TemplateName::setBkColor(const QString& color) {
  mBkColor = color;
  this->setStyleSheet(QString("TemplateName{"
                              "background-color:%1;"
                              "}")
                          .arg(mBkColor));
}

void TemplateName::initUi() {
  setAttribute(Qt::WA_StyledBackground);
  setBkColor(mBkColor);
}
