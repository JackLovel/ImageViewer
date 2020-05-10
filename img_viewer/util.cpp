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

QString Util::getSplitLast(QString string, QString separator)
{
    return string.split(separator).last();
}

QString Util::getFileDir(QString path, QString separator) {
    int i = path.lastIndexOf(separator);
    int offset = i + 1;
    QString dir = path.mid(0, offset);

    return dir;
}

QStringList Util::getDirBelowFiles(const QString path)
{
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.png";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;
}
