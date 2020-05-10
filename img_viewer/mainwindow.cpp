#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scaleFactor = 1;

    QMap<int, int> desktop = Util::GetScreenResolution();
    int desktopWidth = desktop.firstKey();
    int desktopHeight = desktop[desktopWidth];
    int factor = 2;
    int w = desktopWidth / factor;
    int h = desktopHeight / factor;
//    qDebug() << "width:" << w << "height:" << h;
    this->resize(w, h);

    setWindowTitle("图片查看器");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 缩放图片的公共函数
void MainWindow::scaleImage(double factor)
{
    scaleFactor *= factor;
    QSize size = img.size();
    QSize scaleSize = scaleFactor * size;

    QSize picSize = scaleSize;
    img = img.scaled(picSize, Qt::KeepAspectRatio);

    ui->viewLabel->setPixmap(img);
    ui->viewLabel->resize(scaleSize.width(), scaleSize.height());


//    zoomInAction->setEnabled(scaleFactor < 3.0);
//    zoomOutAction->setEnabled(scaleFactor > 0.333);
}

void MainWindow::on_zoomOutButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 1.25;
//    qDebug() << "放大" << factor;
    scaleImage(factor);
}

void MainWindow::on_zoomInButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 0.8;
    scaleImage(factor);
    QSize size = ui->viewLabel->size();
    qDebug() << "缩小" << size;
}

void MainWindow::on_previousButton_clicked()
{

}

void MainWindow::on_nextButton_clicked()
{

}

void MainWindow::on_turnLeftButton_clicked()
{

}

void MainWindow::on_turnRightButton_clicked()
{

}

void MainWindow::on_removeButton_clicked()
{

}

// 打开图片
void MainWindow::on_openButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "打开图片",
                                                "/",
                                                tr("图片文件 (*.png *.jpg)"));
    if (path.isEmpty()) {
        return;
    } else {
        QPixmap tmp(path);
        img = tmp;
        int w = img.width();
        int h = img.height();
        ui->viewLabel->resize(w, h);
        ui->viewLabel->setPixmap(img);
    }
}

//bool MainWindow::loadFile(const QString &fileName)
//{
//    QImageReader reader(fileName);
//    reader.setAutoTransform(true);

//    const QImage newImage = reader.read();
//    if (newImage.isNull()) {
//        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                                 tr("Cannot load %1: %2")
//                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));

//        return false;
//    }

//    setImage(newImage);
//    setWindowFilePath(fileName);

//    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
//            .arg(QDir::toNativeSeparators(fileName))
//            .arg(image.width())
//            .arg(image.height())
//            .arg(image.depth());

//    statusBar()->showMessage(message);
//    return true;
//}

//void MainWindow::setImage(const QImage &newImage)
//{
//    image = newImage;
//    ui->viewLabel->setPixmap(QPixmap::fromImage(image));
//    scaleFactor = 1.0;

//    scrollArea->setVisible(true);
//    printAction->setEnabled(true);
//    fitToWindowAction->setEnabled(true);

//    updateActions();
//    if (!fitToWindowAction->isChecked())
//        imageLabel->adjustSize();
//}


