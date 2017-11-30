#include "RunProgramModule.h"
#include "ProgramItem.h"
#include "qfreedesktop/DesktopEntryFile.h"
//#include "qfreedesktop/IconFile.h"

#include <QDirIterator>
#include <QtCore>

namespace smart_modules {

QStringList getExecutablesFromPath()
{
    QStringList result;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains("PATH")) {
        QString pathVariable = env.value("PATH", "");
        auto dirs = pathVariable.split(":", QString::SkipEmptyParts);
        for (const auto& dir : dirs) {
            QDirIterator it(dir, QDir::Files | QDir::Executable);
            while (it.hasNext())
                result.append(it.next());
        }
    }

    return result;
}

void RunProgramModule::updateProgramsFromPath()
{
    for (const QString& path : getExecutablesFromPath()) {
        if (programs.find(path) != programs.end())
            continue;

        updateProgram(RunProgramModuleProgram(path));
    }
}

void RunProgramModule::updateProgramsFromDesktopFilesDirectory(const QString& dirPath)
{
    using namespace qfreedesktop;

    QDir directory(dirPath);
    if (!directory.exists())
        return;

    QDirIterator it(dirPath, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString path = it.next();

        if (!path.endsWith(".desktop"))
            continue;

        DesktopEntryFile desktopFile(path);

        if (!desktopFile.isValid())
            continue;

        QString exec = desktopFile.getItem("Desktop Entry", "Exec");
        if (exec.size() == 0)
            continue;

        // TODO: convert exec to path
        RunProgramModuleProgram program(exec);

        program.name = desktopFile.getItem("Desktop Entry", "Name");
        program.description = desktopFile.getItem("Desktop Entry", "Comment");
        program.iconPath = desktopFile.getItem("Desktop Entry", "Icon");
        QString terminal = desktopFile.getItem("Desktop Entry", "Terminal");

        if (terminal == "true")
            program.terminal = true;
        else if (terminal == "false")
            program.terminal = false;

        updateProgram(program);
    }
}

void RunProgramModule::updateProgram(const RunProgramModuleProgram& program)
{
    if (program.path.isEmpty())
        return;

    auto it = programs.find(program.path);

    if (it == programs.end()) {
        programs.insert(program.path, program);
    } else {
        RunProgramModuleProgram& p = *it;

        if (!program.name.isEmpty())
            p.name = program.name;

        if (!program.description.isEmpty())
            p.description = program.description;

        if (!program.iconPath.isEmpty())
            p.iconPath = program.iconPath;

        if (program.terminal.isValid())
            p.terminal = program.terminal.toBool();
    }
}

RunProgramModule::RunProgramModule()
{
}

void RunProgramModule::init()
{
    updateProgramsFromPath();
}

void RunProgramModule::update()
{
    // TODO: split it to parts
    updateProgramsFromDesktopFilesDirectory("/usr/share/applications");
    //    updateProgramsFromDesktopFilesDirectory("/usr/share/");
}
bool RunProgramModule::needsUpdating()
{
    return true;
}

QVector<Item*> RunProgramModule::getItems(const QString& input, int count)
{
    QVector<Item*> result;

    if (count == 0)
        return result;

    for (const RunProgramModuleProgram& program : programs) {
        int similarity = program.compareToString(input);
        if (similarity > 0) {
            auto item = new ProgramItem(this, program);
            item->setPriority(similarity);
            result.append(item);
        }

        if (count > 0 && result.size() >= count)
            break;
    }

    return result;
}

QString RunProgramModule::getModuleName()
{
    return "run";
}

QString RunProgramModule::getModuleUniqueName()
{
    return "admin@d3d.info/RunProgramModule";
}

QVector<QString> RunProgramModule::getModuleLinks()
{
    return {
        "run",
        "run program",
        "runprogram",
        "runprogrammodule",
        "exec",
        "start",
    };
}
}
