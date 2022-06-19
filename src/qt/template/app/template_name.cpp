// Created by %username% on %date%.
//
// Copyright (c) %year% The %SharedlibName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
