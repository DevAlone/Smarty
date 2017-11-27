#ifndef RUNPROGRAMMODULE_H
#define RUNPROGRAMMODULE_H

#include "../Module.h"

#include <QIcon>
#include <QSet>
#include <QString>

namespace smart_modules {

struct RunProgramModuleProgram;

class RunProgramModule : public Module {
public:
    RunProgramModule();

    virtual QList<QObject*> getItems(const QString& input, int count);
    virtual QString getModuleName();
    virtual QString getModuleUniqueName();
    virtual QVector<QString> getModuleLinks();

private:
    QSet<RunProgramModuleProgram> programs;
};

struct RunProgramModuleProgram {
    RunProgramModuleProgram(const QString& path, const QString& name = "", const QIcon& icon = QIcon())
        : path(path)
        , name(name)
        , icon(icon)
    {
    }
    QString path;
    // may be empty
    QIcon icon;
    // may be empty
    QString name;
};

inline bool operator==(const RunProgramModuleProgram& left, const RunProgramModuleProgram& right)
{
    return left.path == right.path;
}

inline uint qHash(const RunProgramModuleProgram& obj, uint seed = 0)
{
    return qHash(obj.path, seed ^ 0xa03f);
}
}

#endif // RUNPROGRAMMODULE_H
