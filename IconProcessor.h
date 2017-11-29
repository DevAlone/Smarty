#ifndef ICONPROCESSOR_H
#define ICONPROCESSOR_H

#include <QString>

class IconProcessor {
public:
    IconProcessor();

    /// returns absolute path to icon or empty string
    static QString resolveIconPath(const QString& iconName);
};

#endif // ICONPROCESSOR_H
