#include "InputParser.h"
#include "Item.h"

#include "smart_modules/modules.h"

#include <QSettings>

#include <QDebug>

InputParser::InputParser(QObject* parent)
    : QObject(parent)
{
    modulesManager = ModulesManager::getInstance();
}

QPair<QString, QString> getKeyValue(const QString& str, size_t index)
{
    return QPair<QString, QString>(
        str.left(index).simplified(),
        str.right(str.size() - index - 1).trimmed());
}

QList<QObject*> InputParser::parse(const QString& input)
{
    QVector<Item*> resultItems;

    if (input.size() == 0)
        return QList<QObject*>();

    QSettings settings;

    QVector<smart_modules::Module*> guessedModules;

    QChar delimiter = settings.value("smarty/parser/delimiterSymbol", ':').toChar();

    int delimiterPosition = input.indexOf(delimiter);
    if (delimiterPosition != -1) {
        // module is defined clearly
        auto keyVal = getKeyValue(input, delimiterPosition);
        auto module = modulesManager->getModuleByLink(keyVal.first);

        if (module)
            guessedModules.append(module);
        else
            guessedModules = guessModules(input);
    } else {
        // try to guess module
        guessedModules = guessModules(input);
    }

    int itemsFromModuleCount = settings.value("smarty/parser/itemsFromModuleCount", -1).toInt();
    if (itemsFromModuleCount < 0)
        itemsFromModuleCount = -1;

    for (smart_modules::Module* module : guessedModules) {
        auto items = module->getItems(input, itemsFromModuleCount);
        for (int i = 0; i < items.size(); ++i) {
            if (itemsFromModuleCount >= 0 && i < itemsFromModuleCount)
                break;

            auto item = dynamic_cast<Item*>(items[i]);
            if (item)
                resultItems.append(items[i]);
        }
    }

    qSort(resultItems.begin(), resultItems.end(), [](Item* left, Item* right) {
        return !(*left < *right);
    });

    QList<QObject*> result;

    for (Item* item : resultItems)
        result.append(item);

    return result;
}

QVector<smart_modules::Module*> InputParser::guessModules(const QString&)
{
    QVector<smart_modules::Module*> result;

    for (const auto& pair : modulesManager->getModules()) {
        result.append(pair.second);
    }

    return result;
}
