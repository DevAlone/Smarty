#include "ProgramItem.h"

#include <QtCore>

#include <IconProcessor.h>
#include <QDebug>

namespace smart_modules {
ProgramItem::ProgramItem(const QString& path)
    : TextItem(path)
    , path(path)
{
    if (this->data.size() < 1)
        this->data = path;
}

ProgramItem::ProgramItem(const RunProgramModuleProgram& program)
    : ProgramItem(program.path)
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
