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

private slots:
    void on_zoomOutButton_clicked();

    void on_zoomInButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_turnLeftButton_clicked();

    void on_turnRightButton_clicked();

    void on_removeButton_clicked();

    void on_openButton_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap img;
//    QLabel *imageLabel;       // 用于图片显示
    QScrollArea *scrollArea;  // 滚动区域
    double scaleFactor;       // 缩放比例
    double tmpFactor = 0;

//    bool loadFile(const QString &imgPath);
//    void setImage(const QImage &img);
    void scaleImage(double factor);
};
#endif // MAINWINDOW_H
