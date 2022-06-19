// Created by %username% on %date%.
//
// Copyright (c) %year% The %TemplateName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "template_name_window.h"

#include <QBoxLayout>

#include "template_name.h"

TemplateNameWindow::TemplateNameWindow() : QWidget(nullptr) {
  QVBoxLayout *main_layout = new QVBoxLayout();
  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  TemplateName *content = new TemplateName(this);
  main_layout->addWidget(content, 0);
  this->setLayout(main_layout);

  this->setMinimumSize(800, 600);
  this->setWindowTitle("TemplateName");
}
