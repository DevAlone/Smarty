#include "InputParser.h"
#include "Item.h"

#include "smart_modules/modules.h"

#include <QSettings>

InputParser::InputParser(QObject* parent)
    : QObject(parent)
{
    //    registerModule(smart_modules::TestModule::getInstance());
    registerModule<smart_modules::TestModule>();
    registerModule<smart_modules::NotTestModule>();
}

QPair<QString, QString> getKeyValue(const QString& str, size_t index)
{
    return QPair<QString, QString>(
        str.left(index).simplified(),
        str.right(str.size() - index - 1).trimmed());
}

QList<QObject*> InputParser::parse(const QString& input)
{
    QList<QObject*> result;
    if (input.size() == 0)
        return result;

    QSettings settings;

    QVector<smart_modules::Module*> guessedModules;

    QChar delimiter = settings.value("smarty/parser/delimiterSymbol", ':').toChar();

    int delimiterPosition = input.indexOf(delimiter);
    if (delimiterPosition != -1) {
        // module is defined clearly
        auto keyVal = getKeyValue(input, delimiterPosition);
        auto module = getModuleByLink(keyVal.first);

        if (module)
            guessedModules.append(module);
        else
            guessedModules = guessModules(input);
    } else {
        // try to guess module
        guessedModules = guessModules(input);
    }

    int itemsFromModuleCount = settings.value("smarty/parser/itemsFromModuleCount", 5).toInt();
    if (itemsFromModuleCount < 1)
        itemsFromModuleCount = 5;

    for (smart_modules::Module* module : guessedModules) {
        auto items = module->getItems(input, itemsFromModuleCount);
        for (int i = 0; i < itemsFromModuleCount && i < items.size(); ++i) {
            auto item = dynamic_cast<Item*>(items[i]);
            if (item) {
                item->setModuleName(module->getModuleName());
                result.append(items[i]);
            }
        }
    }

    return result;
}

QVector<smart_modules::Module*> InputParser::guessModules(const QString& input)
{
    QVector<smart_modules::Module*> result;

    for (const auto& pair : modules) {
        result.append(pair.second);
    }

    return result;
}

void InputParser::registerModule(smart_modules::Module* singleton)
{
    modules[typeid(*singleton)] = singleton;

    for (const auto& link : singleton->getModuleLinks()) {
        modulesByLink[link.toLower().toStdString()] = singleton;
    }
}

smart_modules::Module* InputParser::getModuleByLink(const QString& link)
{
    return getModuleByLink(link.toLower().toStdString());
}

smart_modules::Module* InputParser::getModuleByLink(const std::string& link)
{
    if (modulesByLink.find(link) == modulesByLink.end())
        return nullptr;

    return modulesByLink[link];
}
