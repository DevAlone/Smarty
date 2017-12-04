#include "IconProcessor.h"

#include <QFileInfo>

#include <qfreedesktop/IconDatabase.h>
#include <qfreedesktop/IconFile.h>

IconProcessor::IconProcessor()
{
}

QString IconProcessor::resolveIconPath(const QString& iconName)
{
    // TODO: maybe remove it
    QFileInfo fileInfo(iconName);
    if (fileInfo.exists() && fileInfo.isFile())
        return fileInfo.absoluteFilePath();

    // TODO: make it crossplatform
    return qfreedesktop::IconDatabase::getIconPath(iconName);
}
