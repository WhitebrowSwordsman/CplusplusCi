// Created by %username% on %date%.
//
// Copyright (c) %year% The %TemplateName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QWidget>

class TemplateName : public QWidget {
  Q_OBJECT

 public:
  explicit TemplateName(QWidget* parent = nullptr) : QWidget(parent) { InitUi(); }

  void SetBackgroundColor(const QString& color);

 private:
  void InitUi();

  QString background_color_{"cornsilk"};
};
