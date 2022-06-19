//  Created by WhitebrowSwordsman on 2022/06/19.
//
//  Copyright (c) 2022 The CplusplusCi Authors. All rights reserved.
//  Use of this source code is governed by a BSD-style license that can be
//  found in the LICENSE file.

#include "web_view.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>
#include <QWebEngineProfile>

namespace webui {

WebView::WebView(QWidget *parent /* = nullptr*/) : QWebEngineView(parent) { Init(); }

void WebView::contextMenuEvent(QContextMenuEvent *event) {
  const QWebEngineContextMenuData &data = page()->contextMenuData();

  if (!data.isContentEditable()) {
    QWebEngineView::contextMenuEvent(event);
    return;
  }

  QWebEngineProfile *profile = page()->profile();
  const QStringList &languages = profile->spellCheckLanguages();
  QMenu *menu = page()->createStandardContextMenu();
  menu->addSeparator();

  QAction *spellcheck_act = new QAction(tr("Check Spelling"), nullptr);
  spellcheck_act->setCheckable(true);
  spellcheck_act->setChecked(profile->isSpellCheckEnabled());
  connect(spellcheck_act, &QAction::toggled, this, [profile](bool toogled) { profile->setSpellCheckEnabled(toogled); });
  menu->addAction(spellcheck_act);

  if (profile->isSpellCheckEnabled()) {
    QMenu *submenu = menu->addMenu("Select Language");
    const QStringList keys = spell_check_languages_.keys();
    for (const QString &str : keys) {
      QAction *action = submenu->addAction(str);
      action->setCheckable(true);
      QString lang = spell_check_languages_[str];
      action->setChecked(languages.contains(lang));
      connect(action, &QAction::triggered, this, [profile, lang]() { profile->setSpellCheckLanguages(QStringList() << lang); });
    }
  }

  connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
  menu->popup(event->globalPos());
}

void WebView::Init() {
  spell_check_languages_["English"] = "en-US";
  QWebEngineProfile *profile = page()->profile();
  profile->setSpellCheckEnabled(true);
  profile->setSpellCheckLanguages({"en-US"});
}

}  // namespace webui
