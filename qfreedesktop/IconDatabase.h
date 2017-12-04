#ifndef ICONDATABASE_H
#define ICONDATABASE_H

#include "Icon.h"

#include <QMap>
#include <QSet>
#include <QVector>

namespace qfreedesktop {

class IconDatabase {
public:
    static IconDatabase& getInstance();
    static QString getIconPath(const QString& iconName);
    static void init();

private:
    IconDatabase();
    void _init();
    QString _getIconPath(const QString& iconName);

    void indexThemeDirectory(const QString& path, const QString& themeName);
    void indexDirectory(
        const QString& path, const QString& themeName = "",
        ICON_TYPE type = ICON_TYPE::THRESHOLD,
        int size = 0, ICON_CONTEXT context = ICON_CONTEXT::NONE);

    QMap<QString, Icon> icons;
    QMap<QString, QVector<Icon const*>> iconsByFileName;
    // simplified means in lower case and without extension
    QMap<QString, QVector<Icon const*>> iconsBySimplifiedFileName;
};
}

#endif // ICONDATABASE_H
