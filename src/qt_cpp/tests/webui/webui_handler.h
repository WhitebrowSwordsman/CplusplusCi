// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QWebEngineUrlSchemeHandler>

class WebuiHandler : public QWebEngineUrlSchemeHandler {
  Q_OBJECT

 public:
  explicit WebuiHandler(QObject *parent = nullptr);

  void requestStarted(QWebEngineUrlRequestJob *job) override;

  static void RegisterUrlScheme();

  static const QByteArray scheme_name_;
  static const QUrl about_url_;
};
