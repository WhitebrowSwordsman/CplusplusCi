// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webui.h"

#include <QAction>
#include <QBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineView>

#include "web_view.h"
#include "webui_handler.h"

Webui::Webui(QWidget* parent /* = nullptr*/) : QWidget(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setMinimumSize(800, 600);
  setWindowTitle("Webui");
  Init();
}

Webui::~Webui() { UnInit(); }

void Webui::Init() {
  QVBoxLayout* main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);
  main_layout->setSpacing(0);

  menubar_ = new QMenuBar(this);
  main_layout->setMenuBar(menubar_);

  QWidget* line = new QWidget(this);
  line->setFixedHeight(2);
  line->setStyleSheet("background-color:red");
  main_layout->addWidget(line, 0, Qt::AlignTop);

  CreateActions();
  CreateMenus();
}

void Webui::UnInit() {}

void Webui::CreateActions() {
  about_act_ = new QAction("About");
  connect(about_act_, &QAction::triggered, this, &Webui::OnAbout);

  spell_checker_act_ = new QAction("Spell Checker");
  connect(spell_checker_act_, &QAction::triggered, this, &Webui::OnSpellChecker);
}

void Webui::CreateMenus() {
  view_menu_ = new QMenu("View", menubar_);
  view_menu_->addAction(spell_checker_act_);

  help_menu_ = new QMenu("Help", menubar_);
  help_menu_->addAction(about_act_);

  menubar_->addMenu(view_menu_);
  menubar_->addMenu(help_menu_);
}

void Webui::OnAbout() {
  WebuiHandler::RegisterUrlScheme();

  QWebEngineProfile* profile = new QWebEngineProfile;
  WebuiHandler* handler = new WebuiHandler;
  profile->installUrlSchemeHandler(WebuiHandler::scheme_name_, handler);

  QWebEnginePage* page = new QWebEnginePage(profile);
  page->load(WebuiHandler::about_url_);

  QWebEngineView* view = new QWebEngineView();
  view->setAttribute(Qt::WA_DeleteOnClose);
  connect(view, &QObject::destroyed, [profile, handler, page]() {
    delete page;
    delete handler;
    delete profile;
  });
  view->setPage(page);
  view->setContextMenuPolicy(Qt::NoContextMenu);
  view->resize(500, 600);
  view->show();
}

void Webui::OnSpellChecker() {
  webui::WebView* view = new webui::WebView();
  view->setAttribute(Qt::WA_DeleteOnClose);

  view->setUrl(QUrl(QStringLiteral("qrc:/tests/webui/index.html")));
  view->resize(500, 640);
  view->show();
}
