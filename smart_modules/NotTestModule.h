#ifndef NOTTESTMODULE_H
#define NOTTESTMODULE_H

#include "Module.h"

namespace smart_modules {
class NotTestModule : public Module {
public:
    template <typename ModuleType>
    friend ModuleType* getModuleInstance();

    virtual QList<QObject*> getItems(const QString& input, int count);
    virtual QString getModuleName();
    virtual QString getModuleUniqueName();
    virtual QVector<QString> getModuleLinks();

private:
    NotTestModule();
};
}

#endif // NOTTESTMODULE_H
