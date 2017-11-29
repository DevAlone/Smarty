#include "RunProgramModuleProgram.h"

RunProgramModuleProgram::RunProgramModuleProgram(const QString& path, const QString& name, const QString& iconPath)
    : path(path)
    , iconPath(iconPath)
    , name(name)
{
}

//RunProgramModuleProgram::RunProgramModuleProgram(const RunProgramModuleProgram& obj)
//{
//    iconPath = obj.iconPath;
//    name = obj.name;
//    terminal = obj.terminal;
//    description = obj.description;
//}

RunProgramModuleProgram& RunProgramModuleProgram::operator=(const RunProgramModuleProgram& obj)
{
    iconPath = obj.iconPath;
    name = obj.name;
    terminal = obj.terminal;
    description = obj.description;

    return *this;
}
