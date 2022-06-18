#include "template_name_window.h"

#include <QBoxLayout>

#include "template_name.h"

TemplateNameWindow::TemplateNameWindow() : QWidget(nullptr) {
  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->setSpacing(0);
  mainLayout->setMargin(0);
  TemplateName *content = new TemplateName(this);
  mainLayout->addWidget(content, 0);
  this->setLayout(mainLayout);

  this->setMinimumSize(800, 600);
  this->setWindowTitle("TemplateName");
}
