#include "mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    initUi();
    viewer();

    connect(openAction, &QAction::triggered, this, &MainWindow::openSlot);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsSlot);
    connect(printAction, &QAction::triggered, this, &MainWindow::printSlot);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitSlot);

    connect(copyAction, &QAction::triggered, this, &MainWindow::copySlot);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteSlot);

    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomInSlot);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOutSlot);
    connect(fitToWindowAction, &QAction::triggered, this, &MainWindow::fitToWindowSlot);

    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutSlot);

    setWindowTitle("图片查看器");
    // QMap<int, int> Util::GetScreenResolution()
//    QMap<int, int> desktop = Util::GetScreenResolution();
//    int width = desktop.firstKey() / 2;
//    int height = desktop[width] / 2;
//    qDebug() << "width:" << width << "height:" << height;
//    this->resize(width, height);

    move(0, 0);
}

MainWindow::~MainWindow()
{

}



void MainWindow::initUi()
{
    scaleFactor = 1;
    fileMenu = menuBar()->addMenu("文件");
    editMenu = menuBar()->addMenu("编辑");
    viewMenu = menuBar()->addMenu("查看");
    helpMenu = menuBar()->addMenu("帮助");

    openAction = new QAction("打开");
    openAction->setShortcut(tr("CTRL+O"));
    saveAsAction = new QAction("保存");
    saveAsAction->setShortcut(tr("CTRL+SHIFT+S"));
    printAction = new QAction("打印");
    printAction->setShortcut(tr("CTRL+P"));
    exitAction = new QAction("退出");
    exitAction->setShortcut(tr("CTRL+Q"));
    copyAction = new QAction("拷贝");
    copyAction->setShortcut(tr("CTRL+C"));
    pasteAction = new QAction("粘贴");
    pasteAction->setShortcut(tr("CTRL+V"));
    zoomInAction = new QAction("放大 (25%)");
    zoomInAction->setShortcut(tr("CTRL++"));
    zoomOutAction = new QAction("缩小(25%)");
    zoomOutAction->setShortcut(tr("CTRL+-"));
    normalSizeAction = new QAction("重置");
    normalSizeAction->setShortcut(tr("CTRL+S"));
    fitToWindowAction = new QAction("全屏");
    fitToWindowAction->setShortcut(tr("CTRL+F"));
    fitToWindowAction->setCheckable(true);
    aboutAction = new QAction("关于");

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(normalSizeAction);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAction);

    helpMenu->addAction(aboutAction);
}

void MainWindow::viewer()
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);
}

static void initializeImageFileDialog(QFileDialog &dialog,
    QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;

        const QStringList pictureLocations =  QStandardPaths::
            standardLocations(QStandardPaths::PicturesLocation);

        dialog.setDirectory(pictureLocations.isEmpty() ?
            QDir::currentPath() : pictureLocations.last());
    }

    QStringList mimeTypeFilters;
      const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
          ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();


    foreach (const QByteArray &mimeTypeName, supportedMimeTypes) {
        mimeTypeFilters.append(mimeTypeName);
    }

    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix("jpg");
    }
}

void MainWindow::openSlot()
{
    QFileDialog dialog(this,  tr("Open File"));

    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void MainWindow::saveAsSlot()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while(dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

bool MainWindow::saveFile(const QString &fileName) {
    QImageWriter writer(fileName);

    if (!writer.write(image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2").arg(QDir::toNativeSeparators(fileName)), writer.errorString());

        return false;
    }

    const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}


void MainWindow::printSlot()
{
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
}

void MainWindow::exitSlot()
{
    QApplication::exit();
}

void MainWindow::copySlot()
{
    QGuiApplication::clipboard()->setImage(image);
}

static QImage clipboardImage()
{
    if (const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData()) {
        if (mimeData->hasImage()) {
            const QImage image = qvariant_cast<QImage>(mimeData->imageData());
            if (!image.isNull()) {
                return image;
            }
        }
    }

    return QImage();
}

void MainWindow::pasteSlot()
{
    const QImage newImage = clipboardImage();
    if (newImage.isNull()) {
        statusBar()->showMessage("No image in clipboard");
    } else {
        setImage(newImage);
        setWindowFilePath(QString());
        const QString message = tr("Obtained image from clipboard, %1x%2, Depth: %3")
                .arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
        statusBar()->showMessage(message);
    }
}

void MainWindow::scaleImage(double factor)
{
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAction->setEnabled(scaleFactor < 3.0);
    zoomOutAction->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep() / 2)));
}
void MainWindow::zoomInSlot()
{
    scaleImage(1.25);
}

void MainWindow::zoomOutSlot()
{
    scaleImage(0.8);
}

void MainWindow::normalSizeSlot()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void MainWindow::fitToWindowSlot()
{
    bool fitToWindow = fitToWindowAction->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow)
        normalSizeSlot();
    updateActions();
}

void MainWindow::aboutSlot()
{
    QMessageBox::about(this, tr("About Image Viewer"), tr("this is a simple image viewer"));
}


bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);

    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));

        return false;
    }

    setImage(newImage);
    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
            .arg(QDir::toNativeSeparators(fileName))
            .arg(image.width())
            .arg(image.height())
            .arg(image.depth());

    statusBar()->showMessage(message);
    return true;
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    scrollArea->setVisible(true);
    printAction->setEnabled(true);
    fitToWindowAction->setEnabled(true);

    updateActions();
    if (!fitToWindowAction->isChecked())
        imageLabel->adjustSize();
}

void MainWindow::updateActions()
{
    saveAsAction->setEnabled(!image.isNull());
    copyAction->setEnabled(!image.isNull());
    zoomInAction->setEnabled(!fitToWindowAction->isChecked());
    zoomOutAction->setEnabled(!fitToWindowAction->isChecked());
    normalSizeAction->setEnabled(!fitToWindowAction->isChecked());
}
