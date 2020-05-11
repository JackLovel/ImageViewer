#include "util.h"

#include <QApplication>
#include <QDesktopWidget>


// 获取桌面的分辨率
QMap<int, int> Util::GetScreenResolution() {
    QMap<int, int> map;

    QDesktopWidget* desktop = QApplication::desktop();
    int width = desktop->width();
    int height = desktop->height();
    map[width] = height;

    return map;
}
