// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "qt_cpp_main_window.h"

#include <QCoreApplication>
#include <QDebug>
#include <QImageWriter>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

#include "base/base.h"
#include "tests/analog_clock/analog_clock.h"
#include "tests/image_test/image_test_window.h"
#include "tests/scribble/scribble_window.h"
#include "tests/webui/webui.h"

QtCppMainWindow::QtCppMainWindow(QWidget* parent) : QMainWindow(parent) {
  SetupUi();
  setWindowTitle(tr("qt_cpp_app"));

  Init();
}

QtCppMainWindow::~QtCppMainWindow() {}

void QtCppMainWindow::SetupUi() {
  if (this->objectName().isEmpty()) this->setObjectName(QString::fromUtf8("QtCppMainWindow"));
  this->resize(800, 600);
  QWidget* central_widget = new QWidget(this);
  central_widget->setObjectName(QString::fromUtf8("central_widget"));
  this->setCentralWidget(central_widget);
  QMenuBar* menubar = new QMenuBar(this);
  menubar->setObjectName(QString::fromUtf8("menubar"));
  menubar->setGeometry(QRect(0, 0, 800, 21));
  this->setMenuBar(menubar);
  QStatusBar* statusbar = new QStatusBar(this);
  statusbar->setObjectName(QString::fromUtf8("statusbar"));
  this->setStatusBar(statusbar);
  QToolBar* tool_bar = new QToolBar(this);
  tool_bar->setObjectName(QString::fromUtf8("toolBar"));
  this->addToolBar(Qt::TopToolBarArea, tool_bar);
  tool_bar->setWindowTitle(tr("toolBar"));

  action_about_ = new QAction(this);
  action_about_->setObjectName(QString::fromUtf8("actionAbout"));
  action_about_->setText(tr("About"));
  QIcon icon_about;
  icon_about.addFile(QString::fromUtf8(":/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
  action_about_->setIcon(icon_about);
  action_exit_ = new QAction(this);
  action_exit_->setObjectName(QString::fromUtf8("actionExit"));
  action_exit_->setText(tr("Exit"));
  QIcon icon_exit;
  icon_exit.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
  action_exit_->setIcon(icon_exit);

  QMenu* menu_help = new QMenu(menubar);
  menu_help->setObjectName(QString::fromUtf8("menuHelp"));
  menu_help->setTitle(tr("Help"));

  menubar->addAction(menu_help->menuAction());
  menu_help->addAction(action_about_);
  menu_help->addSeparator();
  menu_help->addAction(action_exit_);

  tool_bar->addAction(action_about_);
  tool_bar->addSeparator();
  tool_bar->addAction(action_exit_);

  menu_window_ = new QMenu(menubar);
  menu_window_->setTitle("window");
  menubar->insertAction(menu_help->menuAction(), menu_window_->menuAction());
  CreateImageTestWindowAction();
  CreateScribbleWindowAction();
  CreateAnalogClockAction();
  CreateWebuiAction();
}

void QtCppMainWindow::Init() {
  connect(action_about_, &QAction::triggered, this, &QtCppMainWindow::OnAbout);
  connect(action_exit_, &QAction::triggered, this, &QtCppMainWindow::OnExit);
}

void QtCppMainWindow::CreateImageTestWindowAction() {
  QAction* action = new QAction(this);
  action->setText("ImageTestWindow");
  menu_window_->addAction(action);
  connect(action, &QAction::triggered, [&]() {
    ImageTestWindow* image_test = new ImageTestWindow();
    image_test->show();
  });
}

void QtCppMainWindow::CreateScribbleWindowAction() {
  QAction* action = new QAction(this);
  action->setText("ScribbleWindow");
  menu_window_->addAction(action);
  connect(action, &QAction::triggered, [&]() {
    ScribbleWindow* scribble = new ScribbleWindow();
    scribble->show();
  });
}

void QtCppMainWindow::CreateAnalogClockAction() {
  QAction* action = new QAction(this);
  action->setText("AnalogClock");
  menu_window_->addAction(action);
  connect(action, &QAction::triggered, [&]() {
    AnalogClock* clock = new AnalogClock();
    clock->show();
  });
}

void QtCppMainWindow::CreateWebuiAction() {
  QAction* action = new QAction(this);
  action->setText("Webui");
  menu_window_->addAction(action);
  connect(action, &QAction::triggered, [&]() {
    Webui* webui = new Webui();
    webui->show();
  });
}

void QtCppMainWindow::OnAbout() {
  qDebug() << "";
  QMessageBox::about(this, tr("qt_cpp_app"), QString("<b>QtCppApp</b> : base version is %1").arg(BASE::GetVersion()));

  const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
  for (const QByteArray& format : imageFormats) {
    QString text = tr("%1...").arg(QString(format).toUpper());
    qDebug() << "imageFormats" << text;
  }
}
void QtCppMainWindow::OnExit() {
  qDebug() << "";
  QCoreApplication::quit();
}
