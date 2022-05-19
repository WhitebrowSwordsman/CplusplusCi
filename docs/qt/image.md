# QImage

QImage.

1. Create QImage.
   ```c++
   #include <QCoreApplication>
   #include <QImage>
   #include <QMessageBox>

   QImage OpenImage(const QString& file_name) {
     QImage loaded_image;
     if (loaded_image.load(file_name)) {
       return loaded_image;
     }
     return QImage();
   }
   QImage TestOpenImage() {
     QString image_path = QCoreApplication::applicationDirPath() + "/images/mandrill_512.png";
     auto image = OpenImage(image_path);
     if (image.isNull()) {
       QMessageBox::warning(nullptr, "OpenImage", QString("open <b>%1</b> image failed").arg(image_path));
     }
     return image;
   }

   void DefaultCleanupFunc(void* cleanup_info) { delete[] static_cast<uchar*>(cleanup_info); }
   QImage OpenBGRA32ImageData(const uchar* image_data, int width, int height, QImageCleanupFunction cleanup = DefaultCleanupFunc) {
     return QImage(image_data, width, height, QImage::Format_ARGB32, cleanup, (void*)image_data);
   }
   QImage TestOpenImageData() {
     constexpr const int kImageSideLength = 256;
     constexpr const int kImageBorderWidth = 10;
     constexpr const int kPixelWidth = 4;
     auto pixels = std::make_unique<uchar[]>(kImageSideLength * kImageSideLength * 4);
     for (int i = 0; i < kImageSideLength; i++) {
       for (int j = 0; j < kImageSideLength; j++) {
         bool opaque = true;
         if (i < kImageBorderWidth || j < kImageBorderWidth || i > (kImageSideLength - kImageBorderWidth) ||
             j > (kImageSideLength - kImageBorderWidth)) {
           opaque = false;
         }
         pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth] = 255;      // B
         pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 1] = 0;    // G
         pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 2] = 0;    // R
         pixels[i * kImageSideLength * kPixelWidth + j * kPixelWidth + 3] = 255;  // A
       }
     }
     return OpenBGRA32ImageData(pixels.release(), kImageSideLength, kImageSideLength);
   }
   ```

2. Save QImage
   ```c++
   #include <QCoreApplication>
   #include <QDateTime>
   #include <QImage>
   #include <QPainter>
   
   bool SaveImage(QImage image, const QString& file_name, const char* file_format = "png") {
     if (image.save(file_name, file_format)) {
       return true;
     }
     return false;
   }
   QImage GetCurrentDateTimeImage() {
     constexpr const int kImageSideLength = 256;
     QImage cache_image(kImageSideLength, kImageSideLength, QImage::Format_ARGB32);
     cache_image.fill(Qt::transparent);
     QPainter painter(&cache_image);
     QDateTime timestamp = QDateTime::currentDateTime();
     QString image_text = timestamp.toString("yyyy-MM-dd_hh-mm-ss");
     QTextOption text_option;
     text_option.setAlignment(Qt::AlignCenter);
     painter.save();
     painter.drawText(QRect(0, 0, kImageSideLength, kImageSideLength), image_text, text_option);
     painter.restore();
     return cache_image;
   }
   void TestSaveImage() {
     QDateTime timestamp = QDateTime::currentDateTime();
     QString time_str = timestamp.toString("yyyy-MM-dd_hh-mm-ss");
     QString save_path = QString("%1/images/tmp_%2.png").arg(QCoreApplication::applicationDirPath()).arg(time_str);
     auto image = GetCurrentDateTimeImage();
     if (!image.isNull()) {
       SaveImage(image, save_path);
     }
   }
   ```

3. Set widget background image with QImage.
   ```c++
   #include <QImage>
   #include <QWidget>
   
   void SetWidgetBkImage(QWidget* widget, QImage image) {
     auto scaled_image = image.scaled(widget->size(), Qt::IgnoreAspectRatio);
     QPalette palette;
     QBrush background_brush(scaled_image);
     palette.setBrush(QPalette::Window, background_brush);
     widget->setPalette(palette);
     widget->setAutoFillBackground(true);
   }
   ```

4. Draw something to QImage.
   ```c++
   #include <QCoreApplication>
   #include <QImage>
   #include <QPainter>
   
   void DrawCircleOnImage(QImage& image) {
     QPainter painter(&image);
     painter.setPen(QColor(Qt::red));
     painter.drawEllipse(QRect(QPoint(0, 0), image.size()));
   }
   QImage TestDrawCircleOnImage() {
     constexpr const int kImageSideLength = 256;
     QImage cache_image(kImageSideLength, kImageSideLength, QImage::Format_ARGB32);
     cache_image.fill(Qt::transparent);
     DrawCircleOnImage(cache_image);
     return cache_image;
   }
   ```
