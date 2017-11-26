#include "NotTestModule.h"

#include "../Item.h"

namespace smart_modules {
NotTestModule* NotTestModule::getInstance()
{
    static NotTestModule* obj = new NotTestModule;

    return obj;
}

NotTestModule::NotTestModule()
{
}

QList<QObject*> NotTestModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;

    for (int i = 0; i < count; ++i) {
        result.append(new Item());
    }

    return result;
}

QString NotTestModule::getModuleName()
{
    return "not test module";
}

QString NotTestModule::getModuleUniqueName()
{
    return "admin@d3d.info/NotTestModule";
}

QVector<QString> NotTestModule::getModuleLinks()
{
    return { "NotTestModule" };
}
}
