#ifndef PROGRAMITEM_H
#define PROGRAMITEM_H

#include "../../TextItem.h"

#include "RunProgramModule.h"
namespace smart_modules {
class ProgramItem : public TextItem {
    Q_OBJECT

public:
    ProgramItem(smart_modules::Module* module, const QString& path);
    ProgramItem(smart_modules::Module* module, const RunProgramModuleProgram& program);

    virtual void action();

    QString getPath() const;

private:
    QString path;
};
}
#endif // PROGRAMITEM_H
