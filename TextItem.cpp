#include "TextItem.h"

TextItem::TextItem(smart_modules::Module* module, const QString& data, QObject* parent)
    : Item(module, parent)
    , data(data)
{
    type = Item::TEXT_ITEM;
}

QString TextItem::getData() const
{
    return data;
}

void TextItem::setData(const QString& value)
{
    data = value;
    emit dataChanged(data);
}
