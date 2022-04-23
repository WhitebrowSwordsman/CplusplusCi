#pragma once

#include <QMainWindow>
class QAction;

class QtCppMainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QtCppMainWindow(QWidget* parent = nullptr);
  ~QtCppMainWindow();

 private:
  void setupUi();

 private slots:
  void OnAbout();
  void OnExit();

 private:
  QAction* action_about_{nullptr};
  QAction* action_exit_{nullptr};
};
