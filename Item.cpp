#include "Item.h"

#include <QDebug>

Item::Item(const QString& data, const QIcon& icon, QObject* parent)
    : QObject(parent)
    , data(data)
    , icon(icon)
{
}

QString Item::getData() const
{
    return data;
}

void Item::setData(const QString& value)
{
    data = value;
    emit dataChanged(data);
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
    qDebug() << "action of model with data: " << data;
}
