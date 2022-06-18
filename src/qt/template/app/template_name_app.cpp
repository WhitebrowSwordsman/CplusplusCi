#include <QApplication>

#include "template_name_window.h"

int main(int argc, char* argv[]) {
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);   // DPI support
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);  // HiDPI pixmaps
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication app(argc, argv);
  TemplateNameWindow window;
  window.show();
  return app.exec();
}
