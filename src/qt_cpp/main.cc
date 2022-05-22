#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QTranslator>

#include "qt_cpp_main_window.h"

int main(int argc, char *argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);   // DPI support
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);  // HiDPI pixmaps
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication a(argc, argv);
#if defined(WIN32)
  a.setWindowIcon(QIcon(":/icons/window.ico"));
#endif
  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "qt_cpp_app_" + QLocale(locale).name();
    qDebug() << "baseName is " << baseName;
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  QtCppMainWindow w;
  w.show();
  return a.exec();
}
