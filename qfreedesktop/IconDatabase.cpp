#include "IconDatabase.h"
#include "DesktopEntryFile.h"

#include <QDirIterator>
#include <QProcessEnvironment>
#include <QString>
#include <QtCore>

namespace qfreedesktop {
IconDatabase& IconDatabase::getInstance()
{
    static IconDatabase obj;

    return obj;
}

QString IconDatabase::getIconPath(const QString& iconName)
{
    return getInstance()._getIconPath(iconName);
}

QString IconDatabase::_getIconPath(const QString& iconName)
{

    if (iconsByFileName.find(iconName) != iconsByFileName.end()) {
        const QVector<Icon const*>& icons = iconsByFileName[iconName];

        if (!icons.empty()) {
            auto it = std::max_element(icons.begin(), icons.end(),
                [](Icon const* left, Icon const* right) {
                    int leftSize = left->size.isValid() ? left->size.toInt() : 0;
                    int rightSize = right->size.isValid() ? right->size.toInt() : 0;
                    return leftSize > rightSize;
                });
            return (*it)->path;
        }
    }

    if (iconsBySimplifiedFileName.find(iconName) != iconsBySimplifiedFileName.end()) {
        const QVector<Icon const*>& icons = iconsBySimplifiedFileName[iconName];

        if (!icons.empty()) {
            auto it = std::max_element(icons.begin(), icons.end(),
                [](Icon const* left, Icon const* right) {
                    int leftSize = left->size.isValid() ? left->size.toInt() : 0;
                    int rightSize = right->size.isValid() ? right->size.toInt() : 0;
                    return leftSize > rightSize;
                });
            return (*it)->path;
        }
    }

    return "";
}

void IconDatabase::init()
{
    getInstance()._init();
}

void IconDatabase::_init()
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains("HOME")) {
        QString pathVariable = env.value("HOME", "");
        QDir dir(pathVariable);
        dir = dir.absoluteFilePath(".icons");

        indexDirectory(dir.absolutePath());
    }

    if (env.contains("XDG_DATA_DIRS")) {
        QString var = env.value("XDG_DATA_DIRS", "");
        QStringList dirs = var.split(':', QString::SkipEmptyParts);
        for (const QString& dir : dirs) {
            // TODO: rewrite it
            QString resDir = QDir(dir).absoluteFilePath("icons");
            QDirIterator it(resDir, QDir::Dirs);
            while (it.hasNext()) {
                QString themePath = it.next();
                QFileInfo themeFileInfo;
                QString themeName = themeFileInfo.fileName();
                if (themeName == "hicolor")
                    continue;

                indexThemeDirectory(themePath, themeName);
            }

            QDir hicolorPath = QDir(resDir).absoluteFilePath("hicolor");
            indexThemeDirectory(hicolorPath.absolutePath(), hicolorPath.dirName());
        }
    }

    indexDirectory("/usr/share/pixmaps");

    // It's not specified in specification,
    // but some programs put its icons here
    indexDirectory("/usr/local/share/pixmaps");
}

IconDatabase::IconDatabase()
{
}

void IconDatabase::indexThemeDirectory(const QString& path, const QString& themeName)
{
    QFileInfo themeDirFileInfo(path);
    if (!themeDirFileInfo.exists() || !themeDirFileInfo.isDir())
        return;

    QFileInfo indexThemeFile(QDir(path).absoluteFilePath("index.theme"));
    // TODO: maybe try to find anyway
    if (!indexThemeFile.exists() || !indexThemeFile.isFile())
        return;

    // TODO: change to index theme class
    DesktopEntryFile indexTheme(indexThemeFile.absoluteFilePath());

    QStringList directories = indexTheme.getItem("Icon Theme", "Directories").split(',');

    for (const QString& directory : directories) {
        ICON_TYPE iconType = ICON_TYPE::THRESHOLD;
        QString iconTypeString = indexTheme.getItem(directory, "Type").toLower();
        if (iconTypeString == "scalable")
            iconType = ICON_TYPE::SCALABLE;
        else if (iconTypeString == "fixed")
            iconType = ICON_TYPE::FIXED;

        bool isOk;
        int iconSize = indexTheme.getItem(directory, "Size").toInt(&isOk);
        if (!isOk)
            iconSize = 32;
        ICON_CONTEXT iconContext = ICON_CONTEXT::NONE;
        QString iconContextString = indexTheme.getItem(directory, "Context");

        if (iconContextString == "Actions")
            iconContext = ICON_CONTEXT::ACTIONS;
        else if (iconContextString == "Devices")
            iconContext = ICON_CONTEXT::DEVICES;
        else if (iconContextString == "FileSystems")
            iconContext = ICON_CONTEXT::FILESYSTEMS;
        else if (iconContextString == "MimeTypes")
            iconContext = ICON_CONTEXT::MIMETYPES;
        // TODO: implement max, min size and other features

        indexDirectory(
            QDir(path).absoluteFilePath(directory), themeName,
            iconType, iconSize, iconContext);
    }
}

void IconDatabase::indexDirectory(
    const QString& path, const QString& themeName,
    ICON_TYPE type, int size, ICON_CONTEXT context)
{
    QFileInfo fileInfo(path);
    if (!fileInfo.exists() || !fileInfo.isDir())
        return;

    QDirIterator it(path,
        QStringList() << "*.png"
                      << "*.xpm"
                      << "*.svg",
        QDir::Files);

    while (it.hasNext()) {
        QString iconPath = it.next();

        if (icons.find(iconPath) != icons.end())
            continue;

        icons.insert(iconPath, Icon(iconPath));
        Icon& icon = *icons.find(iconPath);
        icon.type = type;
        if (size > 0)
            icon.size = size;
        icon.context = context;
        icon.themeName = themeName;

        QFileInfo iconFileInfo(iconPath);

        iconsByFileName[iconFileInfo.fileName()].append(&icon);
        iconsBySimplifiedFileName[iconFileInfo.baseName().toLower()].append(&icon);
    }
}
}
