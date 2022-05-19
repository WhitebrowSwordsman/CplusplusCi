#pragma once

#include <QWidget>

class QAction;
class QMenu;

class ImageTestWindow : public QWidget {
  Q_OBJECT

 public:
  explicit ImageTestWindow(QWidget* parent = nullptr);
  ~ImageTestWindow() override;

 private:
  void SetupUi();
  void Init();
  void UnInit();

  void CreateActions();

 private slots:
  void OnOpenImage();
  void OnOpenImage2();
  void OnSaveImage();
  void OnDrawCircle();

 private:
  QWidget* content_widget_{nullptr};
  QMenu* test_menu_{nullptr};
};
