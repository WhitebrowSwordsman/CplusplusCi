// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QWidget>

class QAction;
class QMenu;

class ImageTestWindow : public QWidget {
  Q_OBJECT

 public:
  explicit ImageTestWindow(QWidget* parent = nullptr);
  ~ImageTestWindow() override;

 private:
  void SetupUi();
  void Init();
  void UnInit();

  void CreateActions();

 private slots:
  void OnOpenImage();
  void OnOpenImage2();
  void OnSaveImage();
  void OnDrawCircle();

 private:
  QWidget* content_widget_{nullptr};
  QMenu* test_menu_{nullptr};
};
