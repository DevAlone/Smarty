#ifndef MODULESMANAGER_H
#define MODULESMANAGER_H

#include "smart_modules/Module.h"

#include <QObject>
#include <QString>
#include <QVector>

#include <string>
#include <typeindex>
#include <unordered_map>

class ModulesManager : public QObject {
    Q_OBJECT
public:
    static ModulesManager* getInstance();
    // can return nullptr
    smart_modules::Module* getModuleByLink(const QString& link);
    smart_modules::Module* getModuleByLink(const std::string& link);

    void registerModule(smart_modules::Module* singleton);
    template <typename ModuleType>
    void registerModule();

    const std::unordered_map<std::type_index, smart_modules::Module*>& getModules() const;

private:
    explicit ModulesManager(QObject* parent = nullptr);
signals:

public slots:

private:
    std::unordered_map<std::type_index, smart_modules::Module*> modules;
    // TODO: consider using QString due to good unicode support
    std::unordered_map<std::string, smart_modules::Module*> modulesByLink;
};

template <typename ModuleType>
void ModulesManager::registerModule()
{
    //    registerModule(ModuleType::getInstance());
    registerModule(smart_modules::getModuleInstance<ModuleType>());
}

#endif // MODULESMANAGER_H
