// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QMainWindow>

class QAction;
class QMenu;

class QtCppMainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit QtCppMainWindow(QWidget* parent = nullptr);
  ~QtCppMainWindow();

 private:
  void SetupUi();
  void Init();

  void CreateImageTestWindowAction();
  void CreateScribbleWindowAction();
  void CreateAnalogClockAction();
  void CreateWebuiAction();

 private slots:
  void OnAbout();
  void OnExit();

 private:
  QAction* action_about_{nullptr};
  QAction* action_exit_{nullptr};
  QMenu* menu_window_{nullptr};
};
