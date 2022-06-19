// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget {
  Q_OBJECT

 public:
  explicit ScribbleArea(QWidget *parent = nullptr);

  bool OpenImage(const QString &file_name);
  bool SaveImage(const QString &file_name, const char *file_format);
  void SetPenColor(const QColor &new_color);
  QColor PenColor() const { return pen_color_; }
  void SetPenWidth(int new_width);
  int PenWidth() const { return pen_width_; }
  bool IsModified() const { return modified_; }

 public slots:
  void ClearImage();
  void Print();

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

 private:
  void DrawLineTo(const QPoint &end_point);
  void ResizeImage(QImage *image, const QSize &new_size);

  bool modified_{false};
  bool scribbling_{false};
  int pen_width_{1};
  QColor pen_color_{Qt::blue};
  QImage image_;
  QPoint last_point_;
};
