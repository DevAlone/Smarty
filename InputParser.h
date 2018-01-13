#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include "smart_modules/Module.h"

#include "ModulesManager.h"

#include <QObject>

#include <string>
#include <typeindex>
#include <unordered_map>

class InputParser : public QObject {
    Q_OBJECT
public:
    explicit InputParser(QObject* parent = nullptr);

    QList<QObject*> parse(QString input);
    QVector<smart_modules::Module*> guessModules(const QString& input);

signals:

public slots:

private:
    ModulesManager* modulesManager;
};

#endif // INPUTPARSER_H
