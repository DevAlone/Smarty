#ifndef MATHEXPRESSIONEXECUTORMODULE_H
#define MATHEXPRESSIONEXECUTORMODULE_H

#include <smart_modules/Module.h>

namespace smart_modules {
class MathExpressionExecutorModule : public Module {
public:
    template <typename ModuleType>
    friend ModuleType* getModuleInstance();

    void init();
    void update();
    bool needsUpdating();
    QVector<Item*> getItems(const QString& input, int count);
    QString getModuleName();
    QString getModuleUniqueName();
    QVector<QString> getModuleLinks();
};
}

#endif // MATHEXPRESSIONEXECUTORMODULE_H
