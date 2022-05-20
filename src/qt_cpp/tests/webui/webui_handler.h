#pragma once

#include <QWebEngineUrlSchemeHandler>

class WebuiHandler : public QWebEngineUrlSchemeHandler {
  Q_OBJECT

 public:
  explicit WebuiHandler(QObject *parent = nullptr);

  void requestStarted(QWebEngineUrlRequestJob *job) override;

  static void RegisterUrlScheme();

  const static QByteArray scheme_name_;
  const static QUrl about_url_;
};
