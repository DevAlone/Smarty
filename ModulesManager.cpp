#include "ModulesManager.h"

ModulesManager* ModulesManager::getInstance()
{
    static ModulesManager* obj = new ModulesManager;

    return obj;
}

ModulesManager::ModulesManager(QObject* parent)
    : QObject(parent)
{
}

const std::unordered_map<std::type_index, smart_modules::Module*>&
ModulesManager::getModules() const
{
    return modules;
}

void ModulesManager::registerModule(smart_modules::Module* singleton)
{
    modules[typeid(*singleton)] = singleton;

    for (const auto& link : singleton->getModuleLinks()) {
        modulesByLink[link.toLower().toStdString()] = singleton;
    }
}

smart_modules::Module* ModulesManager::getModuleByLink(const QString& link)
{
    return getModuleByLink(link.toLower().toStdString());
}

smart_modules::Module* ModulesManager::getModuleByLink(const std::string& link)
{
    if (modulesByLink.find(link) == modulesByLink.end())
        return nullptr;

    return modulesByLink[link];
}
