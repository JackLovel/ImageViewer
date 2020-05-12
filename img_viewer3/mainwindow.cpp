#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    factor = 1;
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

        float width = img.width();
        float height = img.height();

        img = img.scaled(width*factor, height*factor, Qt::KeepAspectRatio);
        painter.drawImage(0, 0, img);


//        painter.drawPixmap(QRect(0,0,this->width(),pixmap.height()),pixmap);
//        painter.drawText(this->rect(), Qt::AlignHCenter | Qt::AlignBottom);
}

void MainWindow::on_pushButton_clicked()
{
    factor += 1;
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    factor -= 1;
    update();
}
