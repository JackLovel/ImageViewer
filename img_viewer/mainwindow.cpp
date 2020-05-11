#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgDir = "";
    if (img.isNull()) {
        ui->zoomInButton->setEnabled(false);
        ui->zoomOutButton->setEnabled(false);
        ui->previousButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->turnLeftButton->setEnabled(false);
        ui->turnRightButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
        ui->viewLabel->setText("打开一个图片(Ctrl+O)");
    }

    ui->openButton->setShortcut(QKeySequence("Ctrl+O"));

    scaleFactor = 1;
    currentRotate = 0;

    QMap<int, int> desktop = Util::GetScreenResolution();
    int desktopWidth = desktop.firstKey();
    int desktopHeight = desktop[desktopWidth];
    int factor = 2;
    int w = desktopWidth / factor;
    int h = desktopHeight / factor;
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
    if ( scaleFactor >= 0.7 && scaleFactor <= 1.5) {
        tmpFactor = scaleFactor;
        QSize size = img.size();
        QSize scaleSize = tmpFactor * size;

        img = img.scaled(scaleSize, Qt::KeepAspectRatio);

        ui->viewLabel->resize(scaleSize);
        ui->viewLabel->setPixmap(img);

        ui->zoomOutButton->setEnabled(true);
        ui->zoomInButton->setEnabled(true);
        scaleFactor *= factor;
    } else if (scaleFactor < 0.7) {
        scaleFactor = tmpFactor;
        ui->zoomInButton->setEnabled(false);
        ui->zoomOutButton->setEnabled(true);
    } else {
        scaleFactor = tmpFactor;
        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(false);
    }
}

void MainWindow::on_zoomOutButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 1.25;
    scaleImage(factor);
}

void MainWindow::on_zoomInButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 0.8;
    scaleImage(factor);
}

void MainWindow::on_previousButton_clicked()
{
    int minIndex = 0;
    int size = imgList.size();
    if (size == 1) {
        ui->previousButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
    }
    if (imgIndex != minIndex) {
        imgIndex--;
        ui->previousButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    } else {
        imgIndex = minIndex;
        ui->previousButton->setEnabled(false);
        ui->nextButton->setEnabled(true);
    }
    QString dir = imgDir;
    currentImg = imgList[imgIndex];
    QString path = dir + currentImg;

    QPixmap tmp(path);
    img = tmp;
    int w = img.width();
    int h = img.height();
    ui->viewLabel->resize(w, h);
    ui->viewLabel->setPixmap(img);
}

void MainWindow::on_nextButton_clicked()
{
    int size = imgList.size();
    int maxIndex = size - 1;

    if (size == 1) {
        ui->previousButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
    }
    if (imgIndex != maxIndex) {
        imgIndex++;
        ui->previousButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
    } else {
        imgIndex = maxIndex;
        ui->previousButton->setEnabled(true);
        ui->nextButton->setEnabled(false);
    }
    QString dir = imgDir;
    currentImg = imgList[imgIndex];
    QString path = dir + currentImg;

    QPixmap tmp(path);
    img = tmp;
    int w = img.width();
    int h = img.height();
    ui->viewLabel->resize(w, h);
    ui->viewLabel->setPixmap(img);
}

void MainWindow::on_turnLeftButton_clicked()
{
    int offset = 20;
    currentRotate += offset;
    QMatrix matrix;
    matrix.rotate(currentRotate);
    ui->viewLabel->setPixmap(img.transformed(matrix));
    QSize imgSize = img.size();
    ui->viewLabel->resize(imgSize);
}

void MainWindow::on_turnRightButton_clicked()
{
    int offset = 20;
    currentRotate -= offset;
    QSize imgSize = img.size();
    ui->viewLabel->resize(imgSize);

    QMatrix matrix;
    matrix.rotate(currentRotate);
    ui->viewLabel->setPixmap(img.transformed(matrix));
}


void MainWindow::on_removeButton_clicked()
{
//imgList
    QString file = currentImg;
    QString path =  imgDir + currentImg;
    Util::removeFile(path);

    int totalSize = imgList.size();
    qDebug() << "imgIndex" << imgIndex << "totalSize - 1" << totalSize - 1;
    if (imgIndex >= totalSize - 1) {
        ui->viewLabel->clear();
        ui->viewLabel->setText("没有要显示的图片了");
        return;
    }

    if (imgList.size() == 1) {
        imgList.removeAt(imgIndex);
        imgIndex = -1; // 表明目录中没有图片了
        QPixmap clearPix = QPixmap();
        img = clearPix;

        ui->viewLabel->clear();
        ui->viewLabel->setText("没有要显示的图片了");
    } else {
        imgList.removeAt(imgIndex);

        QPixmap tmp;
        currentImg = imgList[imgIndex];
        path = imgDir + currentImg;
        tmp.load(path);
        img = tmp;
        ui->viewLabel->setPixmap(img);
        setWindowTitle(QString("图片查看器: %1").arg(currentImg));
    }
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
        currentImg = Util::getSplitLast(path, "/");
        imgDir = Util::getFileDir(path, "/");
        imgList = Util::getDirBelowFiles(imgDir);

        imgIndex = imgList.indexOf(currentImg);

        QPixmap tmp(path);
        img = tmp;
        int w = img.width();
        int h = img.height();
        ui->viewLabel->resize(w, h);
        ui->viewLabel->setPixmap(img);

        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(true);
        ui->turnLeftButton->setEnabled(true);
        ui->turnRightButton->setEnabled(true);
        ui->removeButton->setEnabled(true);
        ui->nextButton->setEnabled(imgList.size() != 1);
        ui->previousButton->setEnabled(imgList.size() != 1);
    }
}
