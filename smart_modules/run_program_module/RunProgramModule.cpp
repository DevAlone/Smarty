#include "RunProgramModule.h"
#include "ProgramItem.h"

#include <QVector>

#include <QtCore>
//#include <QProcessEnvironment>
#include <QDirIterator>

#include <QDebug>

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

RunProgramModule::RunProgramModule()
{
    for (const QString& path : getExecutablesFromPath()) {
        RunProgramModuleProgram program(path);
        programs.insert(program);
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

QList<QObject*> RunProgramModule::getItems(const QString& input, int count)
{
    QList<QObject*> result;

    if (count == 0)
        return result;

    for (const RunProgramModuleProgram& program : programs) {
        QFileInfo programFileInfo(program.path);
        auto fileName = programFileInfo.fileName();

        if (fileName == input) {
            // max priority
            // TODO: make it better
            result.insert(0, new ProgramItem(program));
        } else if (fileName.startsWith(input)) {
            result.append(new ProgramItem(program));
        } else {
            QString simplifiedFileName = keepOnlyLettersAndDigits(fileName).toLower();
            QString simplifiedInput = keepOnlyLettersAndDigits(input).toLower();

            if (simplifiedFileName.startsWith(simplifiedInput))
                result.append(
                    new ProgramItem(program));
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
