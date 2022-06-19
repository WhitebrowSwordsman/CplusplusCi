// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The ElidedLabel Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <QApplication>

#include "elided_label_window.h"

int main(int argc, char* argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);   // DPI support
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);  // HiDPI pixmaps
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication app(argc, argv);
  ElidedLabelWindow window;
  window.show();
  return app.exec();
}
