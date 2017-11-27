#include "TestModule.h"

// TODO: fix it
#include "../TextItem.h"

#include <iostream>

namespace smart_modules {
TestModule::TestModule()
{
}

QList<QObject*> TestModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;
    size_t c = count >= 0 ? count : 10;
    for (size_t i = 0; i < c; ++i) {
        result.append(new TextItem(QString::number(i)));
    }
    return result;
}
QString TestModule::getModuleName()
{
    return "test module";
}

QString TestModule::getModuleUniqueName()
{
    return "admin@d3d.info/TestModule";
}

QVector<QString> TestModule::getModuleLinks()
{
    return {
        "test",
        "testmodule",
        "test module",
    };
}
}
