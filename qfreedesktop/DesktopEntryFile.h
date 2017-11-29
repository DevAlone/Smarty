#ifndef DESKTOPENTRYFILE_H
#define DESKTOPENTRYFILE_H

#include <QMap>
#include <QString>
#include <QtCore>

namespace qfreedesktop {
class DesktopEntryFile {
public:
    DesktopEntryFile(const QString& path);

    QString getItem(const QString& group, const QString& key, bool* exist = nullptr) const;

    bool isValid() const;

private:
    void parseFile();
    QString path;
    QMap<QString, QMap<QString, QString>> data;
    bool _isValid = false;
};
}

#endif // DESKTOPENTRYFILE_H
