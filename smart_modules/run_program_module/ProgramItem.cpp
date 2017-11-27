#include "ProgramItem.h"

#include <QtCore>

#include <QDebug>

namespace smart_modules {
ProgramItem::ProgramItem(const QString& path, const QString& name, const QIcon& icon)
    : TextItem(name, icon)
    , path(path)
{
    if (this->data.size() < 1)
        this->data = path;
}

ProgramItem::ProgramItem(const RunProgramModuleProgram& program)
    : ProgramItem(program.path, program.name, program.icon)
{
}

void ProgramItem::action()
{
    QProcess process;

    process.startDetached(path);
}
}
