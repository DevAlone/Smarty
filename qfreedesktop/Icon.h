#ifndef ICON_H
#define ICON_H

#include <QString>
#include <QVariant>

namespace qfreedesktop {
enum class ICON_TYPE {
    THRESHOLD = 0, // default
    FIXED,
    SCALABLE
};
enum class ICON_CONTEXT {
    NONE = 0,
    ACTIONS,
    DEVICES,
    FILESYSTEMS,
    MIMETYPES,
};

struct Icon {
    Icon(const QString& path);
    Icon& operator=(const Icon& obj);

    const QString path;
    ICON_TYPE type = ICON_TYPE::THRESHOLD;
    QVariant size;
    ICON_CONTEXT context = ICON_CONTEXT::NONE;
    QString themeName;
};
}

inline bool operator==(
    const qfreedesktop::Icon& left,
    const qfreedesktop::Icon& right)
{
    return left.path == right.path;
}

inline uint qHash(
    const qfreedesktop::Icon& obj,
    uint seed = 0)
{
    return qHash(obj.path, seed ^ 0x0ba3);
}

#endif // ICON_H
