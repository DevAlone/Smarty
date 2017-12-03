#ifndef PROGRAMITEM_H
#define PROGRAMITEM_H

#include "../../TextItem.h"

#include "RunProgramModule.h"
namespace smart_modules {
class ProgramItem : public TextItem {
    Q_OBJECT

    Q_PROPERTY(QString path READ getPath CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)
    Q_PROPERTY(bool terminal READ getTerminal CONSTANT)
public:
    ProgramItem(smart_modules::Module* module,
        const QString& path,
        const QStringList& arguments,
        const QString& description,
        const QVariant& terminal);

    ProgramItem(smart_modules::Module* module, const RunProgramModuleProgram& program);

    virtual void action();

    QString getPath() const;

    QString getDescription() const;

    bool getTerminal() const;

private:
    QString path;
    QStringList arguments;
    QString description;
    bool terminal;
};
}
#endif // PROGRAMITEM_H
