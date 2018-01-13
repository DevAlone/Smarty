#include "ModulesManager.h"
#include "ModulesManagerBackgroundWorker.h"

#include <QGuiApplication>

#include <QDateTime>
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
    auto prevTime = QDateTime::currentMSecsSinceEpoch();

    while (true) {
        prevTime = QDateTime::currentMSecsSinceEpoch();
        bool boostProcessing = false;

        while (!modulesManager->modulesQueue.isEmpty()) {
            auto modulePair = modulesManager->modulesQueue.dequeue();
            auto module = modulePair.second;
            module->init();
            modulesManager->_registerModule(modulePair);
            boostProcessing = true;
        }

        for (const auto& pair : modulesManager->getModules()) {
            smart_modules::Module* module = pair.second;
            if (module->needsUpdating())
                module->update();

            boostProcessing = true;
        }

        size_t sleepInterval = boostProcessing ? 50 : 100;

        if (QDateTime::currentMSecsSinceEpoch() > prevTime + sleepInterval)
            msleep(sleepInterval);
    }
}
