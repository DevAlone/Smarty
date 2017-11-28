#include "Item.h"

#include <QDebug>

Item::Item(QObject* parent)
    : QObject(parent)
{
    type = ITEM_TYPE::ITEM;
}

QString Item::getModuleName() const
{
    return moduleName;
}

void Item::setModuleName(const QString& value)
{
    moduleName = value;
    emit moduleNameChanged(moduleName);
}

void Item::action()
{
    //    qDebug() << "action of model";
}

Item::ITEM_TYPE Item::getType() const
{
    return type;
}

bool Item::getSmartyShouldBeClosed() const
{
    return smartyShouldBeClosed;
}

QString Item::getIconPath() const
{
    return iconPath;
}

void Item::setIconPath(const QString& value)
{
    iconPath = value;
    emit iconPathChanged(iconPath);
}
