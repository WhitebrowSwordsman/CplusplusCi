// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QWebEngineView>

namespace webui {

class WebView : public QWebEngineView {
  Q_OBJECT

 public:
  explicit WebView(QWidget *parent = nullptr);

 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;

 private:
  void Init();

 private:
  QMap<QString, QString> spell_check_languages_;
};

}  // namespace webui
