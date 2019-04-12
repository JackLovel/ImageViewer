#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(600, 500);
    w.move(500, 100);
    w.show();

    return a.exec();
}
