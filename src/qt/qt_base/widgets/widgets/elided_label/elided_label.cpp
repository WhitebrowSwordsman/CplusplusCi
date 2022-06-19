// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The ElidedLabel Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "elided_label.h"

#include <QPainter>
#include <QTextLayout>

ElidedLabel::ElidedLabel(const QString& text, QWidget* parent/* = nullptr*/) : QFrame(parent), text_(text) {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  InitUi();
}

void ElidedLabel::SetText(const QString& text) {
  text_ = text;
  update();
}

void ElidedLabel::SetBackgroundColor(const QString& color) {
  background_color_ = color;
  this->setStyleSheet(QString("ElidedLabel{"
                              "background-color:%1;"
                              "}")
                          .arg(background_color_));
}

void ElidedLabel::paintEvent(QPaintEvent* evt) {
  QFrame::paintEvent(evt);

  QPainter painter(this);
  QFontMetrics font_metrics = painter.fontMetrics();

  bool did_elide = false;
  int line_spacing = font_metrics.lineSpacing();
  int y = 0;

  QTextLayout text_layout(text_, painter.font());
  text_layout.beginLayout();
  for (;;) {
    QTextLine line = text_layout.createLine();

    if (!line.isValid()) {
      break;
    }

    line.setLineWidth(width());
    int next_line_y = y + line_spacing;

    if (height() >= next_line_y + line_spacing) {
      line.draw(&painter, QPoint(0, y));
      y = next_line_y;
    } else {
      QString last_line = text_.mid(line.textStart());
      QString elided_last_line = font_metrics.elidedText(last_line, Qt::ElideRight, width());
      painter.drawText(QPoint(0, y + font_metrics.ascent()), elided_last_line);
      line = text_layout.createLine();
      did_elide = line.isValid();
      break;
    }
  }
  text_layout.endLayout();

  if (did_elide != elided_) {
    elided_ = did_elide;
    emit ElisionChanged(did_elide);
  }
}

void ElidedLabel::InitUi() {
  setAttribute(Qt::WA_StyledBackground);
  SetBackgroundColor(background_color_);
}
