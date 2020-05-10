#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QDir>
#include <QSettings>

class Util : public QObject
{
public:
    Util();
    ~Util();

   static QMap<int, int> GetScreenResolution();
};

#endif // UTIL_H
