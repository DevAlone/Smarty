#include "InputProcessor.h"

#include <QDebug>
#include <QGuiApplication>

InputProcessor::InputProcessor(QObject* parent)
    : QObject(parent)
{
    //    thread = new BackgroundInputProcessor(this);
    thread = BackgroundInputProcessor::getInstance();
    if (!thread->isRunning())
        thread->start();

    connect(
        thread, &BackgroundInputProcessor::processingStarted,
        this, &InputProcessor::processingStarted);

    connect(
        thread, &BackgroundInputProcessor::processingFinished,
        this, &InputProcessor::threadFinished);
}

InputProcessor::~InputProcessor()
{
    //    thread->stop(10);
}

void InputProcessor::processInput(const QString& input)
{
    lastInput = input;
    thread->processInput(lastInput);
}

bool InputProcessor::processKey(Qt::Key key)
{
    switch (key) {
    case Qt::Key_Tab:
        //        qDebug() << "Tab";
        break;
    default:
        return false;
        break;
    }
    return true;
}

void InputProcessor::threadFinished(QList<QObject*> items)
{
    emit processingFinished(items);
}
