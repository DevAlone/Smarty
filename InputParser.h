#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include "smart_modules/Module.h"

#include <QObject>

#include <string>
#include <typeindex>
#include <unordered_map>

class InputParser : public QObject {
    Q_OBJECT
public:
    explicit InputParser(QObject* parent = nullptr);

    QList<QObject*> parse(const QString& input);
    QVector<smart_modules::Module*> guessModules(const QString& input);

    void registerModule(smart_modules::Module* singleton);
    template <typename ModuleType>
    void registerModule();

signals:

public slots:

private:
    // can return nullptr
    smart_modules::Module* getModuleByLink(const QString& link);
    smart_modules::Module* getModuleByLink(const std::string& link);

    std::unordered_map<std::type_index, smart_modules::Module*> modules;
    // TODO: consider using QString due to good unicode support
    std::unordered_map<std::string, smart_modules::Module*> modulesByLink;
};

template <typename ModuleType>
void InputParser::registerModule()
{
    registerModule(ModuleType::getInstance());
}

#endif // INPUTPARSER_H
