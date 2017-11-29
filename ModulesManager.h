#ifndef MODULESMANAGER_H
#define MODULESMANAGER_H

#include "smart_modules/Module.h"

#include "ModulesManagerBackgroundWorker.h"

#include <QObject>
#include <QString>
#include <QVector>

#include <queue>
#include <string>
#include <typeindex>
#include <unordered_map>

class ModulesManager : public QObject {
    Q_OBJECT
public:
    friend class ModulesManagerBackgroundWorker;

    static ModulesManager* getInstance();
    // can return nullptr
    smart_modules::Module* getModuleByLink(const QString& link);
    smart_modules::Module* getModuleByLink(const std::string& link);

    template <typename ModuleType>
    void registerModule();

    const std::unordered_map<std::type_index, smart_modules::Module*>& getModules() const;

private:
    explicit ModulesManager(QObject* parent = nullptr);

    void _registerModule(smart_modules::Module* module);

    ModulesManagerBackgroundWorker* worker = nullptr;
    std::unordered_map<std::type_index, smart_modules::Module*> modules;
    // TODO: consider using QString due to good unicode support
    std::unordered_map<std::string, smart_modules::Module*> modulesByLink;
    std::queue<smart_modules::Module*> modulesQueue;
};

template <typename ModuleType>
void ModulesManager::registerModule()
{
    modulesQueue.push(smart_modules::getModuleInstance<ModuleType>());
}

#endif // MODULESMANAGER_H
