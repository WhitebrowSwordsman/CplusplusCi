// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The ElidedLabel Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QFrame>

class ElidedLabel : public QFrame {
  Q_OBJECT
  Q_PROPERTY(QString text_ READ GetText WRITE SetText)
  Q_PROPERTY(bool elided_ READ IsElided)

 public:
  explicit ElidedLabel(const QString& text, QWidget* parent = nullptr);

  void SetText(const QString& text);
  const QString& GetText() const { return text_; }
  bool IsElided() const { return elided_; }

  void SetBackgroundColor(const QString& color);

 protected:
  void paintEvent(QPaintEvent* evt) override;

 signals:
  void ElisionChanged(bool elided);

 private:
  void InitUi();

  QString background_color_{"cornsilk"};
  bool elided_{false};
  QString text_;
};
