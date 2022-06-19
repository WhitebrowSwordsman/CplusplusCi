// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "image_test_window.h"

#include <QAction>
#include <QBoxLayout>
#include <QCoreApplication>
#include <QDateTime>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPalette>

ImageTestWindow::ImageTestWindow(QWidget* parent /* = nullptr*/) : QWidget(parent) {
  SetupUi();
  Init();
}

ImageTestWindow::~ImageTestWindow() { UnInit(); }

void ImageTestWindow::SetupUi() {
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
  QMenuBar* menubar = new QMenuBar(this);
  menubar->setGeometry(QRect(0, 0, 800, 21));

  QMenu* menu_help = new QMenu(menubar);
  menu_help->setTitle("Help");
  menubar->addAction(menu_help->menuAction());

  test_menu_ = new QMenu(menubar);
  test_menu_->setTitle("Tests");
  menubar->addAction(test_menu_->menuAction());

  QAction* action_about = new QAction(this);
  action_about->setObjectName(QString::fromUtf8("actionAbout"));
  action_about->setText(tr("About"));
  QIcon icon_about;
  icon_about.addFile(QString::fromUtf8(":/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
  action_about->setIcon(icon_about);
  menu_help->addAction(action_about);
  connect(action_about, &QAction::triggered, []() { QMessageBox::about(nullptr, "ImageTestWindow", "test image functions"); });

  QVBoxLayout* main_layout = new QVBoxLayout();
  main_layout->setContentsMargins(0, 0, 0, 0);
  main_layout->setSpacing(0);
  main_layout->setMenuBar(menubar);
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

  content_widget_ = new QWidget();
  // content_widget_->setObjectName("content_widget_");
  main_layout->addWidget(content_widget_, 1);
}

void ImageTestWindow::Init() {
  setAttribute(Qt::WA_StyledBackground);
  setAttribute(Qt::WA_DeleteOnClose);

#if 0
  content_widget_->setAttribute(Qt::WA_StyledBackground);
  content_widget_->setStyleSheet(QString("QWidget#%1{"
                                         "background-color: #FFFFFF;"
                                         "}")
                                     .arg(content_widget_->objectName()));
#endif
  CreateActions();
}

void ImageTestWindow::UnInit() {}

void ImageTestWindow::CreateActions() {
  QAction* open_action = new QAction("Open Image File");
  connect(open_action, &QAction::triggered, this, &ImageTestWindow::OnOpenImage);
  test_menu_->addAction(open_action);

  QAction* save_action = new QAction("Save Image File");
  connect(save_action, &QAction::triggered, this, &ImageTestWindow::OnSaveImage);
  test_menu_->addAction(save_action);

  QAction* open2_action = new QAction("Open Image Data");
  connect(open2_action, &QAction::triggered, this, &ImageTestWindow::OnOpenImage2);
  test_menu_->addAction(open2_action);

  QAction* draw_cirle_action = new QAction("Draw one circle");
  connect(draw_cirle_action, &QAction::triggered, this, &ImageTestWindow::OnDrawCircle);
  test_menu_->addAction(draw_cirle_action);
}

QImage OpenImage(const QString& file_name) {
  QImage loaded_image;
  if (loaded_image.load(file_name)) {
    return loaded_image;
  }
  return QImage();
}
QImage TestOpenImage() {
  QString image_path = QCoreApplication::applicationDirPath() + "/images/mandrill_512.png";
  auto image = OpenImage(image_path);
  if (image.isNull()) {
    QMessageBox::warning(nullptr, "OpenImage", QString("open <b>%1</b> image failed").arg(image_path));
  }
  return image;
}

void DefaultCleanupFunc(void* cleanup_info) { delete[] static_cast<uchar*>(cleanup_info); }
QImage OpenBGRA32ImageData(const uchar* image_data, int width, int height, QImageCleanupFunction cleanup = DefaultCleanupFunc) {
  return QImage(image_data, width, height, QImage::Format_ARGB32, cleanup,
                reinterpret_cast<void*>(const_cast<uchar*>(image_data)));
}
QImage TestOpenImageData() {
  constexpr const int kImageSideLength = 256;
  constexpr const int kImageBorderWidth = 10;
  constexpr const int kPixelWidth = 4;
  auto pixels = std::make_unique<uchar[]>(kImageSideLength * kImageSideLength * 4);
  for (int i = 0; i < kImageSideLength; i++) {
    for (int j = 0; j < kImageSideLength; j++) {
      bool opaque = true;
      if (i < kImageBorderWidth || j < kImageBorderWidth || i > (kImageSideLength - kImageBorderWidth) ||
          j > (kImageSideLength - kImageBorderWidth)) {
        opaque = false;
      }
      pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth] = 255;      // B
      pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 1] = 0;    // G
      pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 2] = 0;    // R
      pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 3] = 255;  // A
    }
  }
  return OpenBGRA32ImageData(pixels.release(), kImageSideLength, kImageSideLength);
}

bool SaveImage(QImage image, const QString& file_name, const char* file_format = "png") {
  if (image.save(file_name, file_format)) {
    return true;
  }
  return false;
}
QImage GetCurrentDateTimeImage() {
  constexpr const int kImageSideLength = 256;
  QImage cache_image(kImageSideLength, kImageSideLength, QImage::Format_ARGB32);
  cache_image.fill(Qt::transparent);
  QPainter painter(&cache_image);
  QDateTime timestamp = QDateTime::currentDateTime();
  QString image_text = timestamp.toString("yyyy-MM-dd_hh-mm-ss");
  QTextOption text_option;
  text_option.setAlignment(Qt::AlignCenter);
  painter.save();
  painter.drawText(QRect(0, 0, kImageSideLength, kImageSideLength), image_text, text_option);
  painter.restore();
  return cache_image;
}
void TestSaveImage() {
  QDateTime timestamp = QDateTime::currentDateTime();
  QString time_str = timestamp.toString("yyyy-MM-dd_hh-mm-ss");
  QString save_path = QString("%1/images/tmp_%2.png").arg(QCoreApplication::applicationDirPath()).arg(time_str);
  auto image = GetCurrentDateTimeImage();
  if (!image.isNull()) {
    SaveImage(image, save_path);
  }
}

void DrawCircleOnImage(QImage* image) {
  QPainter painter(image);
  painter.setPen(QColor(Qt::red));
  painter.drawEllipse(QRect(QPoint(0, 0), image->size()));
}
QImage TestDrawCircleOnImage() {
  constexpr const int kImageSideLength = 256;
  QImage cache_image(kImageSideLength, kImageSideLength, QImage::Format_ARGB32);
  cache_image.fill(Qt::transparent);
  DrawCircleOnImage(&cache_image);
  return cache_image;
}

void SetWidgetBkImage(QWidget* widget, QImage image) {
  auto scaled_image = image.scaled(widget->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  QBrush background_brush(scaled_image);
  palette.setBrush(QPalette::Window, background_brush);
  widget->setPalette(palette);
  widget->setAutoFillBackground(true);
}

void ImageTestWindow::OnOpenImage() {
  auto image = TestOpenImage();
  if (!image.isNull()) {
    SetWidgetBkImage(content_widget_, image);
  }
}
void ImageTestWindow::OnOpenImage2() {
  auto image = TestOpenImageData();
  SetWidgetBkImage(content_widget_, image);
}
void ImageTestWindow::OnSaveImage() { TestSaveImage(); }
void ImageTestWindow::OnDrawCircle() {
  auto image = TestDrawCircleOnImage();
  SetWidgetBkImage(content_widget_, image);
}
