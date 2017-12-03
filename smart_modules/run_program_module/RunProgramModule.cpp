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
        QString absolutePath = programNameToAbsolutePath(exec);
        if (absolutePath.isEmpty())
            continue;

        RunProgramModuleProgram program(absolutePath);

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

QString RunProgramModule::pathToFileName(const QString& path)
{
    if (path.size() < 1)
        return "";

    QChar quoteChar = '\'';
    bool quoteFound = false;
    if (path.startsWith(quoteChar)) {
        quoteFound = true;
    } else {
        quoteChar = '"';
        if (path.startsWith(quoteChar))
            quoteFound = true;
    }

    if (quoteFound) {
        int posOfSecondQuoteChar = path.indexOf(quoteChar, 1);
        if (posOfSecondQuoteChar >= 0) {
            return path.mid(1, posOfSecondQuoteChar - 1);
        }
    }

    QString fileName;

    for (int i = 0; i < path.size() - 1; ++i) {
        if (path[i] == '\\')
            if (path[i + 1] == ' ') {
                fileName += path[i];
                fileName += path[i + 1];
                ++i;
                continue;
            }

        if (path[i] == ' ')
            return fileName;

        fileName += path[i];
    }
    if (path[path.size() - 1] != ' ')
        fileName += path[path.size() - 1];

    return fileName;
}

void RunProgramModule::updateProgram(const RunProgramModuleProgram& program)
{
    if (program.path.isEmpty())
        return;

    auto it = programs.find(program.path);

    if (it == programs.end()) {
        programs.insert(program.path, program);
        auto fileName = pathToFileName(program.path);
        int indexOfLastSlash = fileName.lastIndexOf('/');
        if (indexOfLastSlash < 0)
            indexOfLastSlash = fileName.lastIndexOf('\\');
        if (indexOfLastSlash >= 0)
            fileName = fileName.mid(indexOfLastSlash + 1);

        const RunProgramModuleProgram& prog = *programs.find(program.path);
        programsByFileNameMap.insert(fileName, &prog);
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

QString RunProgramModule::programNameToAbsolutePath(const QString& name)
{
    // TODO: add options
    QFileInfo file(pathToFileName(name));
    if (file.exists() && file.isFile())
        return file.absoluteFilePath();

    auto it = programsByFileNameMap.find(file.fileName());
    if (it != programsByFileNameMap.end()) {
        RunProgramModuleProgram const* program = *it;
        return program->path;
    }

    return "";
}

void RunProgramModule::init()
{
    updateProgramsFromPath();
}

void RunProgramModule::update()
{
    // TODO: refactor it
    static size_t counter = 0;
    switch (counter) {
    case 0:
        updateProgramsFromDesktopFilesDirectory("/usr/share/applications");
        break;
    case 1:
        updateProgramsFromDesktopFilesDirectory("/usr/local/share/applications");
        break;
    case 2:
        updateProgramsFromDesktopFilesDirectory("~/.local/share/applications");
        break;
    default:
        return;
        break;
    }
    ++counter;
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
