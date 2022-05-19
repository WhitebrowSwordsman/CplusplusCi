#pragma once

#include <QMainWindow>

class QAction;
class QMenu;

class QtCppMainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QtCppMainWindow(QWidget* parent = nullptr);
  ~QtCppMainWindow();

 private:
  void SetupUi();
  void Init();

  void CreateImageTestWindowAction();
  void CreateScribbleWindowAction();

 private slots:
  void OnAbout();
  void OnExit();

 private:
  QAction* action_about_{nullptr};
  QAction* action_exit_{nullptr};
  QMenu* menu_window_{nullptr};
};
