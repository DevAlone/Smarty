#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QString>

namespace smart_modules {
class Module {
public:
    virtual ~Module();

    /// Override these methods in your *Module class

    /// returns list of Item objects
    virtual QList<QObject*> getItems(const QString& input, int count = -1) = 0;

    /// returns moduleName which will be displayed to user
    virtual QString getModuleName() = 0;

    /// returns unique name consisting of
    /// author's email/ClassName
    /// for example: admin@d3d.info/TestModule
    virtual QString getModuleUniqueName() = 0;

    /// returns names which will be used in parser
    virtual QVector<QString> getModuleLinks() = 0;

protected:
    Module();
    Module(const Module&); // = delete;
    Module(Module&&); // = delete;
    void operator=(const Module&);
    void operator=(Module&&);
};
}

#endif // MODULE_H
