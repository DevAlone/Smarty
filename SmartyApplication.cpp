#include "SmartyApplication.h"
#include "BackgroundInputProcessor.h"

#include <QDebug>

SmartyApplication::SmartyApplication(int& argc, char** argv)
    : QGuiApplication(argc, argv)
{
}

void SmartyApplication::close()
{
    qDebug() << "Smarty is closing...";
    auto backgroundInputProcessor = BackgroundInputProcessor::getInstance();
    backgroundInputProcessor->stop(100);
    quit();
}
