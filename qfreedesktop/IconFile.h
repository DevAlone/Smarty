#ifndef ICONFILE_H
#define ICONFILE_H

#include <QtCore>

namespace qfreedesktop {
class IconFile {
public:
    IconFile(const QString& iconName);

    QString getRealAbsolutePath() const;

    bool isValid() const;

private:
    void findIcon(const QString& iconName);
    void setRealAbsolutePath(const QString& path);
    bool tryToSetFilePath(const QString& absolutePath);

    QString realAbsolutePath = "";

    bool _isValid = false;
};
}

#endif // ICONFILE_H
