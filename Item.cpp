#include "Item.h"

#include "smart_modules/Module.h"

#include <QDebug>

Item::Item(smart_modules::Module* module, QObject* parent)
    : QObject(parent)
    , module(module)
{
    type = ITEM_TYPE::ITEM;
}

QString Item::getModuleName() const
{
    if (!module)
        return "";

    return module->getModuleName();
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

int Item::getPriority() const
{
    return priority;
}

bool Item::operator<(const Item& other)
{
    auto modulePriority = module ? module->getPriority() : 0;
    auto otherModulePriority = other.module ? other.module->getPriority() : 0;

    if (modulePriority == otherModulePriority)
        return priority < other.priority;

    return modulePriority < otherModulePriority;
}

void Item::setPriority(int value)
{
    priority = value;
}

QString Item::getRenderer() const
{
    return renderer;
}
