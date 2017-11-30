#include "ProgramItem.h"

#include <QtCore>

#include <IconProcessor.h>
#include <QDebug>

namespace smart_modules {
ProgramItem::ProgramItem(Module* module, const QString& path)
    : TextItem(module, path)
    , path(path)
{
    if (this->data.size() < 1)
        this->data = path;
}

ProgramItem::ProgramItem(Module* module, const RunProgramModuleProgram& program)
    : ProgramItem(module, program.path)
{
    setData(program.name);
    setIconPath(IconProcessor::resolveIconPath(program.iconPath));
    if (data.size() < 1)
        data = program.path;
}

void ProgramItem::action()
{
    QProcess process;

    process.startDetached(path);
}

QString ProgramItem::getPath() const
{
    return path;
}
}
