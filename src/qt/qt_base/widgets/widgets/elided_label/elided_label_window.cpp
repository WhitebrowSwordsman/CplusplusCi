// Created by WhitebrowSwordsman on 2022/06/19.
//
// Copyright (c) 2022 The ElidedLabel Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "elided_label_window.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

#include "elided_label.h"

ElidedLabelWindow::ElidedLabelWindow() : QWidget(nullptr) {
  const QString romeo =
      "But soft, what light through yonder window breaks? / "
      "It is the east, and Juliet is the sun. / "
      "Arise, fair sun, and kill the envious moon, / "
      "Who is already sick and pale with grief / "
      "That thou, her maid, art far more fair than she.";

  const QString macbeth =
      "To-morrow, and to-morrow, and to-morrow, / "
      "Creeps in this petty pace from day to day, / "
      "To the last syllable of recorded time; / "
      "And all our yesterdays have lighted fools / "
      "The way to dusty death. Out, out, brief candle! / "
      "Life's but a walking shadow, a poor player, / "
      "That struts and frets his hour upon the stage, / "
      "And then is heard no more. It is a tale / "
      "Told by an idiot, full of sound and fury, / "
      "Signifying nothing.";

  const QString harry = "Feeling lucky, punk?";

  text_samples_ << romeo << macbeth << harry;

  elided_text_ = new ElidedLabel(text_samples_[sample_index_], this);
  elided_text_->setFrameStyle(QFrame::Box);

  QPushButton *switch_button = new QPushButton("Switch text");
  connect(switch_button, &QPushButton::clicked, this, &ElidedLabelWindow::SwitchText);

  QPushButton *exit_button = new QPushButton("Exit");
  connect(exit_button, &QPushButton::clicked, this, &ElidedLabelWindow::close);

  QLabel *label = new QLabel("Elided");
  label->setVisible(elided_text_->IsElided());
  connect(elided_text_, &ElidedLabel::ElisionChanged, label, &QLabel::setVisible);

  width_slider_ = new QSlider(Qt::Horizontal);
  width_slider_->setMinimum(0);
  connect(width_slider_, &QSlider::valueChanged, this, &ElidedLabelWindow::OnWidthChanged);

  height_slider_ = new QSlider(Qt::Vertical);
  height_slider_->setInvertedAppearance(true);
  height_slider_->setMinimum(0);
  connect(height_slider_, &QSlider::valueChanged, this, &ElidedLabelWindow::OnHeightChanged);

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(label, 0, 1, Qt::AlignCenter);
  layout->addWidget(switch_button, 0, 2);
  layout->addWidget(exit_button, 0, 3);
  layout->addWidget(width_slider_, 1, 1, 1, 3);
  layout->addWidget(height_slider_, 2, 0);
  layout->addWidget(elided_text_, 2, 1, 1, 3, Qt::AlignTop | Qt::AlignLeft);
  setLayout(layout);

  this->setMinimumSize(800, 600);
  this->setWindowTitle("ElidedLabel");
}

void ElidedLabelWindow::resizeEvent(QResizeEvent *evt) {
  Q_UNUSED(evt);

  int max_width = width_slider_->width();
  width_slider_->setMaximum(max_width);
  width_slider_->setValue(max_width / 2);

  int max_height = height_slider_->height();
  height_slider_->setMaximum(max_height);
  height_slider_->setValue(max_height / 2);

  elided_text_->setFixedSize(width_slider_->value(), height_slider_->value());
}

void ElidedLabelWindow::SwitchText() {
  sample_index_ = (sample_index_ + 1) % text_samples_.size();
  elided_text_->SetText(text_samples_.at(sample_index_));
}
void ElidedLabelWindow::OnWidthChanged(int width) { elided_text_->setFixedWidth(width); }
void ElidedLabelWindow::OnHeightChanged(int height) { elided_text_->setFixedHeight(height); }
