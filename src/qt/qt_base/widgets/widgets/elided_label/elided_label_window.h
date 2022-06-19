// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The ElidedLabel Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QWidget>

class ElidedLabel;
class QSlider;

class ElidedLabelWindow : public QWidget {
  Q_OBJECT

 public:
  ElidedLabelWindow();

 protected:
  void resizeEvent(QResizeEvent *evt) override;

 private slots:
  void SwitchText();
  void OnWidthChanged(int width);
  void OnHeightChanged(int height);

 private:
  int sample_index_{0};
  QStringList text_samples_;
  ElidedLabel *elided_text_{nullptr};
  QSlider *height_slider_{nullptr};
  QSlider *width_slider_{nullptr};
};
