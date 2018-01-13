#include "MathExpressionExecutorModule.h"
#include "exprtk.hpp"

#include <TextItem.h>

namespace smart_modules {
void MathExpressionExecutorModule::init()
{
}

void MathExpressionExecutorModule::update()
{
}

bool MathExpressionExecutorModule::needsUpdating()
{
    return false;
}

QVector<Item*> MathExpressionExecutorModule::getItems(const QString& input, int count)
{
    exprtk::parser<double> parser;
    exprtk::expression<double> expression;

    bool isOk = parser.compile(input.toStdString(), expression);

    auto strResult = QString::number(expression.value());

    if (isOk)
        return {
            new TextItem(this, strResult)
        };
    else
        return {};
}

QString MathExpressionExecutorModule::getModuleName()
{
    return "calculate";
}

QString MathExpressionExecutorModule::getModuleUniqueName()
{
    return "admin@d3d.info/MathExpressionExecutorModule";
}

QVector<QString> MathExpressionExecutorModule::getModuleLinks()
{
    return {
        "calculate",
        "calc",
        "c",
        "math",
    };
}
}
