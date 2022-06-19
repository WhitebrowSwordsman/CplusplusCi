// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webui_handler.h"

#include <QApplication>
#include <QFile>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlScheme>

#define SCHEME_NAME "webui"

const QByteArray WebuiHandler::scheme_name_ = QByteArrayLiteral(SCHEME_NAME);
const QUrl WebuiHandler::about_url_ = QUrl(QStringLiteral(SCHEME_NAME ":about"));

WebuiHandler::WebuiHandler(QObject* parent /* = nullptr*/) : QWebEngineUrlSchemeHandler(parent) {}

void WebuiHandler::requestStarted(QWebEngineUrlRequestJob* job) {
  static const QUrl kWebuiOrigin(QStringLiteral(SCHEME_NAME ":"));
  static const QByteArray kGet(QByteArrayLiteral("GET"));
  static const QByteArray kPost(QByteArrayLiteral("POST"));

  QByteArray method = job->requestMethod();
  QUrl url = job->requestUrl();
  QUrl initiator = job->initiator();

  if (method == kGet && url == about_url_) {
    QFile* file = new QFile(QStringLiteral(":/tests/webui/about.html"), job);
    file->open(QIODevice::ReadOnly);
    job->reply(QByteArrayLiteral("text/html"), file);
  } else if (method == kPost && url == about_url_ && initiator == kWebuiOrigin) {
    job->fail(QWebEngineUrlRequestJob::RequestAborted);
    QApplication::exit();
  } else {
    job->fail(QWebEngineUrlRequestJob::UrlNotFound);
  }
}

void WebuiHandler::RegisterUrlScheme() {
  QWebEngineUrlScheme webui_scheme(scheme_name_);
  webui_scheme.setFlags(QWebEngineUrlScheme::SecureScheme | QWebEngineUrlScheme::LocalScheme |
                        QWebEngineUrlScheme::LocalAccessAllowed);
  QWebEngineUrlScheme::registerScheme(webui_scheme);
}
