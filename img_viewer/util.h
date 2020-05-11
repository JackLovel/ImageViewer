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
   static QString getSplitLast(QString string, QString separator);
   static QString getFileDir(QString path, QString separator);
   static QStringList getDirBelowFiles(const QString path);
   static void removeFile(const QString path);
};

#endif // UTIL_H
