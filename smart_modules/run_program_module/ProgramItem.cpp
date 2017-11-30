#include "ProgramItem.h"

#include <QtCore>

#include <IconProcessor.h>
#include <QDebug>

namespace smart_modules {
ProgramItem::ProgramItem(Module* module, const QString& path, const QString& description, const QVariant& terminal)
    : TextItem(module, path)
    , path(path)
    , description(description)
    , terminal(!terminal.isValid() || terminal.toBool())
{
    renderer = "ProgramItemRenderer";

    if (this->data.size() < 1)
        this->data = path;
}

ProgramItem::ProgramItem(Module* module, const RunProgramModuleProgram& program)
    : ProgramItem(module, program.path, program.description, program.terminal)
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

QString ProgramItem::getDescription() const
{
    return description;
}

bool ProgramItem::getTerminal() const
{
    return terminal;
}
}
