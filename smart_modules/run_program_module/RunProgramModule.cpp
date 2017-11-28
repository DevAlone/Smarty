#include "RunProgramModule.h"
#include "ProgramItem.h"
#include "qfreedesktop/DesktopEntryFile.h"
#include "qfreedesktop/IconFile.h"

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

        programs[path] = RunProgramModuleProgram(path);
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

        QString name = desktopFile.getItem("Desktop Entry", "Name");
        QString description = desktopFile.getItem("Desktop Entry", "Comment");
        QString iconPath = IconFile(desktopFile.getItem("Desktop Entry", "Icon"))
                               .getRealAbsolutePath();
        QString terminal = desktopFile.getItem("Desktop Entry", "Terminal");

        // TODO: convert exec to path
        RunProgramModuleProgram program(exec);
        auto it = programs.find(exec);
        if (it != programs.end())
            program = *it;

        if (!name.isEmpty())
            program.name = name;

        if (!description.isEmpty())
            program.description = description;

        if (!iconPath.isEmpty())
            program.iconPath = iconPath;

        if (terminal == "true")
            program.terminal = true;
        else if (terminal == "false")
            program.terminal = false;

        programs[exec] = program;
    }
}

RunProgramModule::RunProgramModule()
{
    updateProgramsFromPath();
    // TODO: make it starting later
    updateProgramsFromDesktopFilesDirectory("/usr/share/applications");
    //    updateProgramsFromDesktopFilesDirectory("/usr/share/");
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

QList<QObject*> RunProgramModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;

    if (count == 0)
        return result;

    for (const RunProgramModuleProgram& program : programs) {
        QFileInfo programFileInfo(program.path);
        auto fileName = programFileInfo.fileName();

        //        if (program.path.contains("python3.5")) {
        //            qDebug() << program.path;
        //        }

        // TODO: optimize it
        if (fileName == input) {
            // max priority
            // TODO: make it better
            result.insert(0, new ProgramItem(program));
        } else if (fileName.startsWith(input)) {
            result.append(new ProgramItem(program));
        } else {
            QString simplifiedFileName = keepOnlyLettersAndDigits(fileName).toLower();
            QString simplifiedInput = keepOnlyLettersAndDigits(input).toLower();

            if (simplifiedFileName.contains(simplifiedInput))
                result.append(new ProgramItem(program));
            else if (containsParts(simplifiedFileName, simplifiedInput))
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
