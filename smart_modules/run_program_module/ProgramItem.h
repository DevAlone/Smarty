#ifndef PROGRAMITEM_H
#define PROGRAMITEM_H

#include "../../TextItem.h"

#include "RunProgramModule.h"
namespace smart_modules {
class ProgramItem : public TextItem {
    Q_OBJECT

public:
    ProgramItem(
        const QString& path,
        const QString& name = "",
        const QIcon& icon = QIcon());
    ProgramItem(const RunProgramModuleProgram& program);

    virtual void action();

private:
    QString path;
};
}
#endif // PROGRAMITEM_H
