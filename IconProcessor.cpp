#include "IconProcessor.h"

#include <QFileInfo>

#include <qfreedesktop/IconFile.h>

IconProcessor::IconProcessor()
{
}

QString IconProcessor::resolveIconPath(const QString& iconName)
{
    QFileInfo fileInfo(iconName);
    if (fileInfo.exists() && fileInfo.isFile())
        return fileInfo.absoluteFilePath();

    // TODO: rewrite it!
    qfreedesktop::IconFile freeDesktopIconFile(iconName);

    if (freeDesktopIconFile.isValid())
        return freeDesktopIconFile.getRealAbsolutePath();

    return "";
}
