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

QString keepOnlyLettersAndDigits(const QString& str)
{
    QString res = "";

    for (QChar ch : str)
        if (ch.isDigit() || ch.isLetter())
            res += ch;

    return res;
}

bool containsParts(const QString& str, const QString& substr, long* match = nullptr)
{
    int strIndex = 0;
    int substrIndex = 0;

    for (; substrIndex < substr.size() && strIndex < str.size(); ++strIndex) {
        if (str[strIndex] == substr[substrIndex])
            ++substrIndex;
        else if (match)
            --*match;
    }

    return substrIndex == (substr.size());
}
long RunProgramModule::compareProgramToInput(
    const RunProgramModuleProgram& program, const QString& input)
{
    QFileInfo programFileInfo(program.path);
    auto fileName = programFileInfo.fileName();

    //    // TODO: optimize it
    //    if (fileName == input) {
    //        // max priority
    //        // TODO: make it better
    //        result.insert(0, new ProgramItem(program));
    //    } else if (fileName.startsWith(input)) {
    //        result.append(new ProgramItem(program));
    //    } else {
    //        QString simplifiedFileName = keepOnlyLettersAndDigits(fileName).toLower();
    //        QString simplifiedInput = keepOnlyLettersAndDigits(input).toLower();

    //        if (simplifiedFileName.contains(simplifiedInput))
    //            result.append(new ProgramItem(program));
    //        else if (containsParts(simplifiedFileName, simplifiedInput))
    //            result.append(new ProgramItem(program));
    //    }
    QString simplifiedInput = keepOnlyLettersAndDigits(input).toLower();

    {
        QString simplifiedField = keepOnlyLettersAndDigits(fileName).toLower();

        if (containsParts(simplifiedField, simplifiedInput))
            return 1000;
    }
    {
        QString simplifiedField = keepOnlyLettersAndDigits(program.name).toLower();

        if (containsParts(simplifiedField, simplifiedInput))
            return 100;
    }
    {
        QString simplifiedField = keepOnlyLettersAndDigits(program.path).toLower();

        if (containsParts(simplifiedField, simplifiedInput))
            return 50;
    }
    {
        QString simplifiedField = keepOnlyLettersAndDigits(program.description).toLower();

        if (containsParts(simplifiedField, simplifiedInput))
            return 10;
    }

    return 0;
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

QList<QObject*> RunProgramModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;

    if (count == 0)
        return result;

    for (const RunProgramModuleProgram& program : programs) {
        if (compareProgramToInput(program, input) > 0) {
            result.append(new ProgramItem(program));
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
