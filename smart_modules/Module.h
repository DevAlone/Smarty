#ifndef MODULE_H
#define MODULE_H

#include <QObject>
#include <QString>

namespace smart_modules {
class Module {
public:
    virtual ~Module();

    /// Implement these methods in your *Module class:
    /// virtual void init() = 0;
    /// virtual QList<QObject*> getItems(const QString& input, int count = -1) = 0;
    /// virtual QString getModuleName() = 0;
    /// virtual QString getModuleUniqueName() = 0;
    /// virtual QVector<QString> getModuleLinks() = 0;

    /// This method will be called on module's initialization(in background thread)
    /// after initialization, module should be workable,
    /// but inititalization have not to waste a lot of time
    virtual void init() = 0;

    /// This method will be calling in background thread
    /// allowing module to make some processes like indexing of filesystem
    /// this method is called often and should take as few time as possible
    virtual void update() = 0;

    /// return true when module should be updated
    virtual bool needsUpdating() = 0;

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

template <typename ModuleType>
ModuleType* getModuleInstance()
{
    static ModuleType* obj = new ModuleType;

    return obj;
}
}

#endif // MODULE_H
