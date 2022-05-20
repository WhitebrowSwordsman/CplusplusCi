#include "web_view.h"

#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>
#include <QWebEngineProfile>

namespace webui {

WebView::WebView(QWidget *parent /* = nullptr*/) : QWebEngineView(parent) {}

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

  connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
  menu->popup(event->globalPos());
}

}  // namespace webui
