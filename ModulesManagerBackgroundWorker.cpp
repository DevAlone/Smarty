#include "ModulesManager.h"
#include "ModulesManagerBackgroundWorker.h"

#include <QGuiApplication>

#include <iostream>

namespace smart_modules {
class Module;
}

ModulesManagerBackgroundWorker::ModulesManagerBackgroundWorker(QObject* parent)
    : QThread(parent)
{
}

void ModulesManagerBackgroundWorker::run()
{
    auto modulesManager = ModulesManager::getInstance();

    while (true) {
        while (!modulesManager->modulesQueue.empty()) {
            auto module = modulesManager->modulesQueue.back();
            modulesManager->modulesQueue.pop();
            module->init();
            modulesManager->_registerModule(module);
        }

        for (const auto& pair : modulesManager->getModules()) {
            smart_modules::Module* module = pair.second;
            if (module->needsUpdating())
                module->update();
        }
        sleep(1);
    }
}
