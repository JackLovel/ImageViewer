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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSlot();
    void saveAsSlot();
    void printSlot();
    void exitSlot();
    void copySlot();
    void pasteSlot();
    void zoomInSlot();
    void zoomOutSlot();
    void normalSizeSlot();
    void fitToWindowSlot();
    void aboutSlot();

private:
    void initUi();
    void viewer();
//    static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode);
    void updateActions();
    void setImage(const QImage &newImage);
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void scaleImage(double factor);

    QImage image;
    QLabel *imageLabel;       // 用于图片显示
    QScrollArea *scrollArea;  // 滚动区域
    double scaleFactor;       // 缩放比例
    QPrinter printer;

    QAction *openAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *normalSizeAction;
    QAction *fitToWindowAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};

#endif // MAINWINDOW_H
