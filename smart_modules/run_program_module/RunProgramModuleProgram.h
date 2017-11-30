#ifndef RUNPROGRAMMODULEPROGRAM_H
#define RUNPROGRAMMODULEPROGRAM_H

#include <QtCore>

struct RunProgramModuleProgram {
    RunProgramModuleProgram(const QString& path, const QString& name = "", const QString& iconPath = "");
    //    RunProgramModuleProgram(const RunProgramModuleProgram& obj);
    RunProgramModuleProgram& operator=(const RunProgramModuleProgram& obj);

    const QString path;

    // may be empty
    // It's either path in fs or icon name in freedesktop's terms
    QString iconPath;

    // may be empty
    QString name;

    // bool field denoting whether application should be runned in terminal or not
    // may be null
    QVariant terminal;

    QString description;

    // <= 0 means program doesn't match to input
    int compareToString(const QString& text) const;
};

inline bool operator==(const RunProgramModuleProgram& left, const RunProgramModuleProgram& right)
{
    return left.path == right.path;
}

inline uint qHash(const RunProgramModuleProgram& obj, uint seed = 0)
{
    return qHash(obj.path, seed ^ 0xa03f);
}
#endif // RUNPROGRAMMODULEPROGRAM_H
