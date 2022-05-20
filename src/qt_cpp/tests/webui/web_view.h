#pragma once

#include <QWebEngineView>

namespace webui {

class WebView : public QWebEngineView {
  Q_OBJECT

 public:
  explicit WebView(QWidget *parent = nullptr);

 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;

 private:
};

}  // namespace webui
