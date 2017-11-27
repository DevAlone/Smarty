#ifndef TESTMODULE_H
#define TESTMODULE_H

#include "Module.h"

namespace smart_modules {
class TestModule : public Module {
public:
    template <typename ModuleType>
    friend ModuleType* getModuleInstance();

    virtual QList<QObject*> getItems(const QString& input, int count = -1);
    virtual QString getModuleName();
    virtual QString getModuleUniqueName();
    virtual QVector<QString> getModuleLinks();

protected:
    TestModule();
};
}

#endif // TESTMODULE_H
