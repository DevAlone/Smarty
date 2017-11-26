#include "InputProcessor.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    qmlRegisterType<InputProcessor>("smarty.input", 1, 0, "InputProcessor");
    qmlRegisterType<Item>("smarty.models", 1, 0, "ItemModel");
    //    qRegisterMetaType<ITEM_TYPE>("ITEM_TYPE");
    //    qmlRegisterType<ITEM_TYPE>("smarty.models", 1, 0, "ITEM_TYPE");
    //    qmlRegister

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("DevAlone");
    app.setOrganizationDomain("d3d.info");
    app.setApplicationName("Smarty");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
