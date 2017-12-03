#include "RunProgramModuleProgram.h"

RunProgramModuleProgram::RunProgramModuleProgram(const QString& path)
    : path(path)
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

int compareStringToPattern(const QString& str, const QString& pattern)
{
    int similarity = std::numeric_limits<int>::max() / 2;

    QString::size_type firstIndex = 0;
    QString::size_type secondIndex = 0;

    for (; firstIndex < str.size() && secondIndex < pattern.size(); ++firstIndex) {
        bool equales = str[firstIndex].toLower() == pattern[secondIndex].toLower();
        bool sameCase = str[firstIndex].isLower() == pattern[secondIndex].isLower();

        if (equales) {
            ++secondIndex;
            similarity += sameCase ? 2 : 1;
        } else {
            similarity -= sameCase ? 1 : 2;
        }
    }

    if (secondIndex != pattern.size())
        return 0;

    if (secondIndex == firstIndex && secondIndex == str.size())
        similarity += pattern.size();

    similarity -= str.size();

    return similarity;
}

int RunProgramModuleProgram::compareToString(const QString& text) const
{
    QFileInfo programFileInfo(path);
    auto fileName = programFileInfo.fileName();

    return std::max({
        compareStringToPattern(fileName, text),
        compareStringToPattern(name, text),
        compareStringToPattern(path, text),
        compareStringToPattern(description, text),
    });
}
