#ifndef PROGRAMITEM_H
#define PROGRAMITEM_H

#include "../../TextItem.h"

#include "RunProgramModule.h"
namespace smart_modules {
class ProgramItem : public TextItem {
    Q_OBJECT

public:
    ProgramItem(const QString& path);
    ProgramItem(const RunProgramModuleProgram& program);

    virtual void action();

    QString getPath() const;

private:
    QString path;
};
}
#endif // PROGRAMITEM_H
