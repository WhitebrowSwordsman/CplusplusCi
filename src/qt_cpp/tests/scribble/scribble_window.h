#pragma once

#include <QWidget>

class QMenuBar;
class QAction;
class QMenu;
class ScribbleArea;

class ScribbleWindow : public QWidget {
  Q_OBJECT

 public:
  explicit ScribbleWindow(QWidget* parent = nullptr);
  ~ScribbleWindow() override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private:
  void SetupUi();
  void Init();
  void UnInit();
  void CreateActions();
  void CreateMenus();
  bool MaybeSave();
  bool SaveFile(const QByteArray& file_format);

 private slots:
  void OnOpen();
  void OnSave();
  void OnPenColor();
  void OnPenWidth();
  void OnAbout();

 private:
  ScribbleArea* scribble_area_{nullptr};

  QMenuBar* menubar_{nullptr};
  QMenu* save_as_menu_{nullptr};
  QMenu* file_menu_{nullptr};
  QMenu* option_menu_{nullptr};
  QMenu* help_menu_{nullptr};

  QAction* open_action_{nullptr};
  QList<QAction*> save_as_actions_;
  QAction* print_action_{nullptr};
  QAction* pen_color_action_{nullptr};
  QAction* pen_width_action_{nullptr};
  QAction* clear_screen_action_{nullptr};
  QAction* about_action_{nullptr};
  QAction* about_qt_action_{nullptr};
};
