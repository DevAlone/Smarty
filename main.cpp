#include "smart_modules/modules.h"

#include "ImageProvider.h"
#include "InputProcessor.h"
#include "RunGuard.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    RunGuard runGuard("Smarty/asdf123sdhf45axcZV");
    if (!runGuard.tryToRun()) {
        qInfo() << QObject::tr("Another instance of Smarty is already runned");
        return 0;
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("DevAlone");
    app.setOrganizationDomain("d3d.info");
    app.setApplicationName("Smarty");

    auto modulesManager = ModulesManager::getInstance();

    modulesManager->registerModule<smart_modules::RunProgramModule>();
    //    modulesManager->registerModule<smart_modules::TestModule>();
    //    modulesManager->registerModule<smart_modules::NotTestModule>();

    qmlRegisterType<InputProcessor>("smarty.input", 1, 0, "InputProcessor");
    qmlRegisterType<Item>("smarty.models", 1, 0, "ItemModel");

    QQmlApplicationEngine engine;

    ImageProvider* imageProvider = new ImageProvider();
    engine.addImageProvider("file", imageProvider);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
