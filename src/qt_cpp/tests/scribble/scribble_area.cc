// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "scribble_area.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#if defined(QT_PRINTSUPPORT_LIB)
#endif

ScribbleArea::ScribbleArea(QWidget* parent /* = nullptr*/) : QWidget(parent) { setAttribute(Qt::WA_StaticContents); }

bool ScribbleArea::OpenImage(const QString& file_name) {
  QImage loaded_image;
  if (!loaded_image.load(file_name)) {
    return false;
  }
  QSize new_size = loaded_image.size().expandedTo(size());
  ResizeImage(&loaded_image, new_size);
  image_ = loaded_image;
  modified_ = false;
  update();
  return true;
}
bool ScribbleArea::SaveImage(const QString& file_name, const char* file_format) {
  QImage visible_image = image_;
  ResizeImage(&visible_image, size());
  if (visible_image.save(file_name, file_format)) {
    modified_ = false;
    return true;
  }
  return false;
}
void ScribbleArea::SetPenColor(const QColor& new_color) { pen_color_ = new_color; }
void ScribbleArea::SetPenWidth(int new_width) { pen_width_ = new_width; }

void ScribbleArea::ClearImage() {
  image_.fill(qRgb(255, 255, 255));
  modified_ = true;
  update();
}
void ScribbleArea::Print() {
#if defined(QT_PRINTSUPPORT_LIB)
#else
  qDebug() << __FUNCTION__;
#endif
}

void ScribbleArea::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    last_point_ = event->pos();
    scribbling_ = true;
  }
}
void ScribbleArea::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton && scribbling_) {
    DrawLineTo(event->pos());
  }
}
void ScribbleArea::mouseReleaseEvent(QMouseEvent* event) {
  if (event->buttons() == Qt::LeftButton && scribbling_) {
    DrawLineTo(event->pos());
    scribbling_ = false;
  }
}
void ScribbleArea::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  QRect dirty_rect = event->rect();
  painter.drawImage(dirty_rect, image_, dirty_rect);
}
void ScribbleArea::resizeEvent(QResizeEvent* event) {
  if (width() > image_.width() || height() > image_.height()) {
    int new_width = qMax(width() + 128, image_.width());
    int new_height = qMax(height() + 128, image_.height());
    ResizeImage(&image_, QSize(new_width, new_height));
    update();
  }
}

void ScribbleArea::DrawLineTo(const QPoint& end_point) {
  QPainter painter(&image_);
  painter.setPen(QPen(pen_color_, pen_width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter.drawLine(last_point_, end_point);
  modified_ = true;
  int rad = (pen_width_ / 2) + 2;
  update(QRect(last_point_, end_point).normalized().adjusted(-rad, -rad, +rad, +rad));
  last_point_ = end_point;
}
void ScribbleArea::ResizeImage(QImage* image, const QSize& new_size) {
  if (image->size() == new_size) {
    return;
  }
  QImage new_image(new_size, QImage::Format_RGB32);
  new_image.fill(qRgb(255, 255, 255));
  QPainter painter(&new_image);
  painter.drawImage(QPoint(0, 0), *image);
  *image = new_image;
}
