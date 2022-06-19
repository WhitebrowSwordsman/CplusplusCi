// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

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
