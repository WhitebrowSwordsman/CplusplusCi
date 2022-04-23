#include "qt_cpp_main_window.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

#include "base/base.h"

QtCppMainWindow::QtCppMainWindow(QWidget* parent) : QMainWindow(parent) {
  setupUi();
  setWindowTitle(tr("qt_cpp_app"));

  connect(action_about_, &QAction::triggered, this, &QtCppMainWindow::OnAbout);
  connect(action_exit_, &QAction::triggered, this, &QtCppMainWindow::OnExit);
}

QtCppMainWindow::~QtCppMainWindow() {}

void QtCppMainWindow::setupUi() {
  if (this->objectName().isEmpty()) this->setObjectName(QString::fromUtf8("QtCppMainWindow"));
  this->resize(800, 600);
  QWidget* central_widget = new QWidget(this);
  central_widget->setObjectName(QString::fromUtf8("central_widget"));
  this->setCentralWidget(central_widget);
  QMenuBar* menubar = new QMenuBar(this);
  menubar->setObjectName(QString::fromUtf8("menubar"));
  menubar->setGeometry(QRect(0, 0, 800, 21));
  this->setMenuBar(menubar);
  QStatusBar* statusbar = new QStatusBar(this);
  statusbar->setObjectName(QString::fromUtf8("statusbar"));
  this->setStatusBar(statusbar);
  QToolBar* tool_bar = new QToolBar(this);
  tool_bar->setObjectName(QString::fromUtf8("toolBar"));
  this->addToolBar(Qt::TopToolBarArea, tool_bar);
  tool_bar->setWindowTitle(tr("toolBar"));

  action_about_ = new QAction(this);
  action_about_->setObjectName(QString::fromUtf8("actionAbout"));
  action_about_->setText(tr("About"));
  QIcon icon_about;
  icon_about.addFile(QString::fromUtf8(":/images/info.png"), QSize(), QIcon::Normal, QIcon::Off);
  action_about_->setIcon(icon_about);
  action_exit_ = new QAction(this);
  action_exit_->setObjectName(QString::fromUtf8("actionExit"));
  action_exit_->setText(tr("Exit"));
  QIcon icon_exit;
  icon_exit.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
  action_exit_->setIcon(icon_exit);

  QMenu* menuHelp = new QMenu(menubar);
  menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
  menuHelp->setTitle(tr("Help"));

  menubar->addAction(menuHelp->menuAction());
  menuHelp->addAction(action_about_);
  menuHelp->addSeparator();
  menuHelp->addAction(action_exit_);

  tool_bar->addAction(action_about_);
  tool_bar->addSeparator();
  tool_bar->addAction(action_exit_);
}

void QtCppMainWindow::OnAbout() {
  qDebug() << "";
  QMessageBox::about(this, tr("qt_cpp_app"), QString("<b>QtCppApp</b> : base version is %1").arg(BASE::GetVersion()));
}
void QtCppMainWindow::OnExit() {
  qDebug() << "";
  QCoreApplication::quit();
}
