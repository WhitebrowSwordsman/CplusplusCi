#pragma once

#include <QWidget>

class QAction;
class QMenuBar;
class QMenu;

class Webui : public QWidget {
  Q_OBJECT

 public:
  explicit Webui(QWidget* parent = nullptr);
  ~Webui() override;

 private:
  void Init();
  void UnInit();
  void CreateActions();
  void CreateMenus();

 private slots:
  void OnAbout();
  void OnSpellChecker();

 private:
  QMenuBar* menubar_{nullptr};
  QAction* about_act_{nullptr};
  QAction* spell_checker_act_{nullptr};
  QMenu* help_menu_{nullptr};
  QMenu* view_menu_{nullptr};
};
