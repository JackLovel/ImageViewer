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

void MainWindow::on_openButton_clicked()
{

}
