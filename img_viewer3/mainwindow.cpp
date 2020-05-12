#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        QImage img;
        QString name = ":/img/demo.png";
        img.load(name);
        painter.drawImage(0, 0, img);


//        painter.drawPixmap(QRect(0,0,this->width(),pixmap.height()),pixmap);
//        painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignBottom);
}
