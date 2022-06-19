// Created by %username% on %date%.
//
// Copyright (c) %year% The %SharedlibName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
