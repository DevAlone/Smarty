#ifndef RUNPROGRAMMODULE_H
#define RUNPROGRAMMODULE_H

#include "RunProgramModuleProgram.h"
#include "smart_modules/Module.h"

#include <QIcon>
#include <QMap>
#include <QSet>
#include <QString>
#include <QVariant>

#include <QDebug>

namespace smart_modules {
class RunProgramModule : public Module {
public:
    RunProgramModule();

    virtual void init();
    virtual void update();
    virtual bool needsUpdating();
    virtual QList<QObject*> getItems(const QString& input, int count);
    virtual QString getModuleName();
    virtual QString getModuleUniqueName();
    virtual QVector<QString> getModuleLinks();

private:
    void updateProgramsFromPath();
    void updateProgramsFromDesktopFilesDirectory(const QString& dirPath);

    void updateProgram(const RunProgramModuleProgram& program);

    // <= 0 means program doesn't match to input
    long compareProgramToInput(const RunProgramModuleProgram& program, const QString& input);
    //    QSet<RunProgramModuleProgram> programs;
    QMap<QString, RunProgramModuleProgram> programs;
    //    QMap<QString, RunProgramModuleProgram const*> programsByPathMap;
    // TODO: programs by name map
    //    QMap<QString, RunProgramModuleProgram> programs;
};
}

#endif // RUNPROGRAMMODULE_H
