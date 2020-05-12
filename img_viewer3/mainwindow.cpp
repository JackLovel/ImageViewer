#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QImage img;
        QString name = ":/img/demo.png";
        img.load(name);
        painter.translate(890,550);
        painter.rotate(rotate);
        painter.translate(-890,-550);

        float width = img.width();
        float height = img.height();

        img = img.scaled(width*factor, height*factor, Qt::KeepAspectRatio);
        painter.drawImage(posX, posY, img);
}

void MainWindow::on_pushButton_clicked()
{
    factor += factorOffset;
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    factor -= factorOffset;
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    rotate += rotateOffset;
    update();
}

void MainWindow::on_pushButton_4_clicked()
{
    rotate -= rotateOffset;
    update();
}

void MainWindow::setup()
{
    ui->setupUi(this);

    factor = 1;
    factorOffset = 1;
    posX = 670;
    posY = 200;
    rotate = 0;
    rotateOffset = 90;

    imgName = ":/img/demo.png";

    setWindowTitle("图片查看器");
}
