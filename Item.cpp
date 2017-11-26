#include "Item.h"

#include <QDebug>

Item::Item(const QIcon& icon, QObject* parent)
    : QObject(parent)
    , icon(icon)
{
    type = ITEM_TYPE::ITEM;
}

QIcon Item::getIcon() const
{
    return icon;
}

void Item::setIcon(const QIcon& value)
{
    icon = value;
    emit iconChanged(icon);
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
    qDebug() << "action of model";
}

Item::ITEM_TYPE Item::getType() const
{
    return type;
}
