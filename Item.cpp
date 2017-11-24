#include "Item.h"

Item::Item(QObject* parent)
    : QObject(parent)
{
}

QString Item::getData() const
{
    return data;
}

void Item::setData(const QString& value)
{
    data = value;
}
