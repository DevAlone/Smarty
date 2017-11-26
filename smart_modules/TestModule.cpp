#include "TestModule.h"

// TODO: fix it
#include "../Item.h"

#include <iostream>

namespace smart_modules {
TestModule::TestModule()
{
}

TestModule* TestModule::getInstance()
{
    static TestModule* obj = new TestModule();

    return obj;
}

class TestItem : public Item {
public:
    TestItem(const QString& str)
        : Item("test item's data: " + str)
        , str(str)
    {
    }
    virtual void action()
    {
        std::cout << "Test action: " << str.toStdString() << std::endl;
    }

private:
    QString str;
};

QList<QObject*> TestModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;
    size_t c = count >= 0 ? count : 10;
    for (size_t i = 0; i < c; ++i) {
        result.append(new TestItem(QString::number(i)));
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
