#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <QScrollArea>
#include <QPrinter>
#include <QApplication>
#include <QtWidgets>
#include <QPrintDialog>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QStringList>
#include <QPrinter>
#include <QRect>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
