// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "scribble_window.h"

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QBoxLayout>

#include "scribble_area.h"

ScribbleWindow::ScribbleWindow(QWidget* parent /* = nullptr*/) : QWidget(parent) {
  SetupUi();
  Init();
}

ScribbleWindow::~ScribbleWindow() { UnInit(); }

void ScribbleWindow::closeEvent(QCloseEvent* event) {
  if (MaybeSave()) {
    event->accept();
  } else {
    event->ignore();
  }
}

void ScribbleWindow::SetupUi() {
  setMinimumSize(800, 600);
  setWindowFlags(Qt::Window);
  setObjectName("ImageTestWindow");
#if 0
  setStyleSheet(
      "QWidget#ImageTestWindow{"
      "background-color: red;"
      "}");
#endif

  // menubar
  menubar_ = new QMenuBar(this);
  menubar_->setGeometry(QRect(0, 0, 800, 21));

  QVBoxLayout* main_layout = new QVBoxLayout();
  main_layout->setContentsMargins(0, 0, 0, 0);
  main_layout->setSpacing(0);
  main_layout->setMenuBar(menubar_);
  setLayout(main_layout);

  QWidget* separator = new QWidget(parentWidget());
  separator->setAttribute(Qt::WA_MouseNoMask, true);
  separator->setAutoFillBackground(false);
  separator->setObjectName("separator");
  separator->setFixedHeight(2);
  separator->setStyleSheet(
      "QWidget#separator{"
      "background-color: #E1D2C8;"
      "}");
  main_layout->addWidget(separator, 0, Qt::AlignTop);
  main_layout->addSpacing(2);

  scribble_area_ = new ScribbleArea();
  scribble_area_->setObjectName("scribble_area_");
  main_layout->addWidget(scribble_area_, 1);
}

void ScribbleWindow::Init() {
  setAttribute(Qt::WA_StyledBackground);
  setAttribute(Qt::WA_DeleteOnClose);

  CreateActions();
  CreateMenus();
}

void ScribbleWindow::UnInit() {}

void ScribbleWindow::CreateActions() {
  open_action_ = new QAction("&Open...", this);
  open_action_->setShortcuts(QKeySequence::Open);
  connect(open_action_, &QAction::triggered, this, &ScribbleWindow::OnOpen);

  const QList<QByteArray> image_formats = QImageWriter::supportedImageFormats();
  for (const auto& format : image_formats) {
    QString text = QString("%1...").arg(QString::fromLatin1(format).toUpper());
    QAction* action = new QAction(text, this);
    action->setData(format);
    connect(action, &QAction::triggered, this, &ScribbleWindow::OnSave);
    save_as_actions_.append(action);
  }

  print_action_ = new QAction("&Print...", this);
  connect(print_action_, &QAction::triggered, scribble_area_, &ScribbleArea::Print);

  pen_color_action_ = new QAction("&Pen Color...", this);
  connect(pen_color_action_, &QAction::triggered, this, &ScribbleWindow::OnPenColor);

  pen_width_action_ = new QAction("Pen &Width...", this);
  connect(pen_width_action_, &QAction::triggered, this, &ScribbleWindow::OnPenWidth);

  clear_screen_action_ = new QAction("&Clear Screen", this);
  connect(clear_screen_action_, &QAction::triggered, scribble_area_, &ScribbleArea::ClearImage);

  about_action_ = new QAction("&About", this);
  connect(about_action_, &QAction::triggered, this, &ScribbleWindow::OnAbout);

  about_qt_action_ = new QAction("About &Qt", this);
  connect(about_qt_action_, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void ScribbleWindow::CreateMenus() {
  save_as_menu_ = new QMenu("&Save As", this);
  for (QAction* action : qAsConst(save_as_actions_)) {
    save_as_menu_->addAction(action);
  }

  file_menu_ = new QMenu("&File", this);
  file_menu_->addAction(open_action_);
  file_menu_->addMenu(save_as_menu_);
  file_menu_->addAction(print_action_);

  option_menu_ = new QMenu("&Options", this);
  option_menu_->addAction(pen_color_action_);
  option_menu_->addAction(pen_width_action_);
  option_menu_->addSeparator();
  option_menu_->addAction(clear_screen_action_);

  help_menu_ = new QMenu("&Help", this);
  help_menu_->addAction(about_action_);
  help_menu_->addAction(about_qt_action_);

  menubar_->addMenu(file_menu_);
  menubar_->addMenu(option_menu_);
  menubar_->addMenu(help_menu_);
}

bool ScribbleWindow::MaybeSave() {
  if (scribble_area_->IsModified()) {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, "Scribble",
                               "The image has been modified.\n"
                               "Do you want to save your changes?",
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save) {
      return SaveFile("png");
    } else if (ret == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}

bool ScribbleWindow::SaveFile(const QByteArray& file_format) {
  QString initial_path = QDir::currentPath() + "/untitled." + file_format;
  QString file_name = QFileDialog::getSaveFileName(this, "Save As", initial_path,
                                                   QString("%1 Files (*.%2);;All Files (*)")
                                                       .arg(QString::fromLatin1(file_format.toUpper()))
                                                       .arg(QString::fromLatin1(file_format)));
  if (file_name.isEmpty()) {
    return false;
  }
  return scribble_area_->SaveImage(file_name, file_format.constData());
}

void ScribbleWindow::OnOpen() {
  if (MaybeSave()) {
    QString file_name = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
    if (!file_name.isEmpty()) {
      scribble_area_->OpenImage(file_name);
    }
  }
}

void ScribbleWindow::OnSave() {
  QAction* action = qobject_cast<QAction*>(sender());
  QByteArray file_format = action->data().toByteArray();
  SaveFile(file_format);
}

void ScribbleWindow::OnPenColor() {
  QColor new_color = QColorDialog::getColor(scribble_area_->PenColor());
  if (new_color.isValid()) {
    scribble_area_->SetPenColor(new_color);
  }
}

void ScribbleWindow::OnPenWidth() {
  bool ok;
  int new_width = QInputDialog::getInt(this, "Scribble", "Select pen width:", scribble_area_->PenWidth(), 1, 50, 1, &ok);
  if (ok) {
    scribble_area_->SetPenWidth(new_width);
  }
}

void ScribbleWindow::OnAbout() {
  QMessageBox::about(this, "About Scribble",
                     "<p>The <b>Scribble</b> example shows how to use QWidget as the "
                     "base widget for an application, and how to reimplement some of "
                     "QWidget's event handlers to receive the events generated for "
                     "the application's widgets:</p><p> We reimplement the mouse event "
                     "handlers to facilitate drawing, the paint event handler to "
                     "update the application and the resize event handler to optimize "
                     "the application's appearance. In addition we reimplement the "
                     "close event handler to intercept the close events before "
                     "terminating the application.</p><p> The example also demonstrates "
                     "how to use QPainter to draw an image in real time, as well as "
                     "to repaint widgets.</p>");
}
