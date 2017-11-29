#include "IconFile.h"

#include <QDebug>

namespace qfreedesktop {
IconFile::IconFile(const QString& iconName)
{
    if (iconName.size() > 0)
        findIcon(iconName);
}

QString IconFile::getRealAbsolutePath() const
{
    return realAbsolutePath;
}

bool IconFile::isValid() const
{
    return _isValid;
}

void IconFile::findIcon(const QString& iconName)
{
    if (tryToSetFilePath(iconName))
        return;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains("HOME")) {
        QString pathVariable = env.value("HOME", "");
        QDir dir(pathVariable);
        dir = dir.absoluteFilePath(".icons");

        if (tryToSetFilePath(dir.absoluteFilePath(iconName)))
            return;
    }

    if (env.contains("XDG_DATA_DIRS")) {
        QString var = env.value("XDG_DATA_DIRS", "");
        QStringList dirs = var.split(':', QString::SkipEmptyParts);
        for (const QString& dir : dirs) {
            // TODO: rewrite it
            QString resDir = QDir(dir).absoluteFilePath("icons");
            resDir = QDir(resDir).absoluteFilePath("hicolor");
            resDir = QDir(resDir).absoluteFilePath("128x128");

            if (tryToSetFilePath(QDir(resDir).absoluteFilePath(iconName)))
                return;
        }
    }

    if (tryToSetFilePath(QDir("/usr/share/pixmaps").absoluteFilePath(iconName)))
        return;

    if (tryToSetFilePath(QDir("/usr/local/share/pixmaps").absoluteFilePath(iconName)))
        return;
}

void IconFile::setRealAbsolutePath(const QString& path)
{
    realAbsolutePath = path;
    _isValid = true;
}

bool isFileExist(const QString& absolutePath)
{
    QFileInfo fileInfo(absolutePath);
    return fileInfo.exists() && fileInfo.isFile();
}

bool IconFile::tryToSetFilePath(const QString& absolutePath)
{
    if (isFileExist(absolutePath)) {
        setRealAbsolutePath(absolutePath);
        return true;
    }

    QFileInfo fileInfo(absolutePath);

    QString baseDir = fileInfo.path();
    QString fileName = fileInfo.fileName();

    QDirIterator it(baseDir, QDir::Files); // TODO: ? , QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString file = it.next();
        QFileInfo fileInfo(file);

        if (fileInfo.fileName().startsWith(fileName)) {
            if (isFileExist(fileInfo.absoluteFilePath())) {
                setRealAbsolutePath(fileInfo.absoluteFilePath());
                return true;
            }
        }
    }

    return false;
}
}
