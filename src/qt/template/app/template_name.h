// Created by %username% on %date%.
//
// Copyright (c) %year% The %SharedlibName% Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
