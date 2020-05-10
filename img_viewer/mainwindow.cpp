#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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


void MainWindow::on_zoomOutButton_clicked()
{

}

void MainWindow::on_zoomInButton_clicked()
{

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
//        qDebug() << path;
        QPixmap img(path);
        int w = img.width();
        int h = img.height();
        ui->viewLabel->setFixedSize(w, h);
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


