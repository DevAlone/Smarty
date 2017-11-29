#include "ModulesManager.h"
#include "ModulesManagerBackgroundWorker.h"

ModulesManager* ModulesManager::getInstance()
{
    static ModulesManager* obj = new ModulesManager;

    return obj;
}

ModulesManager::ModulesManager(QObject* parent)
    : QObject(parent)
{
    worker = new ModulesManagerBackgroundWorker(this);
    worker->start(QThread::LowestPriority);
}

const std::unordered_map<std::type_index, smart_modules::Module*>&
ModulesManager::getModules() const
{
    return modules;
}

void ModulesManager::_registerModule(smart_modules::Module* module)
{
    modules[typeid(*module)] = module;

    for (const auto& link : module->getModuleLinks()) {
        modulesByLink[link.toLower().toStdString()] = module;
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
