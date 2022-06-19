// Created by %username% on %date%.
//
// Copyright (c) %year% The %TemplateName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "template_name.h"

void TemplateName::SetBackgroundColor(const QString& color) {
  background_color_ = color;
  this->setStyleSheet(QString("TemplateName{"
                              "background-color:%1;"
                              "}")
                          .arg(background_color_));
}

void TemplateName::InitUi() {
  setAttribute(Qt::WA_StyledBackground);
  SetBackgroundColor(background_color_);
}
