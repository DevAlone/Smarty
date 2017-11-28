#ifndef RUNPROGRAMMODULE_H
#define RUNPROGRAMMODULE_H

#include "../Module.h"

#include <QIcon>
#include <QMap>
#include <QSet>
#include <QString>
#include <QVariant>

#include <QDebug>

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
    void updateProgramsFromPath();
    void updateProgramsFromDesktopFilesDirectory(const QString& dirPath);

    //    QSet<RunProgramModuleProgram> programs;
    QMap<QString, RunProgramModuleProgram> programs;
};

struct RunProgramModuleProgram {
    RunProgramModuleProgram(const QString& path = "/dev/null", const QString& name = "", const QString& iconPath = "")
        : path(path)
        , name(name)
        , iconPath(iconPath)
    {
    }
    QString path;
    // may be empty
    QString iconPath;
    // may be empty
    QString name;
    // bool field denoting whether application should be runned in terminal or not
    // may be null
    QVariant terminal;
    QString description;
};

//inline bool operator==(const RunProgramModuleProgram& left, const RunProgramModuleProgram& right)
//{
//    return left.path == right.path;
//}

//inline uint qHash(const RunProgramModuleProgram& obj, uint seed = 0)
//{
//    return qHash(obj.path, seed ^ 0xa03f);
//}
}

#endif // RUNPROGRAMMODULE_H
