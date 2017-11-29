#include "BackgroundInputProcessor.h"

#include <QGuiApplication>
#include <iostream>

BackgroundInputProcessor::BackgroundInputProcessor(QObject* parent)
    : QThread(parent)
{
    parser = new InputParser(this);
}

void BackgroundInputProcessor::processInput(const QString& input)
{
    lastInput = input;

    if (isWaiting)
        condition.wakeAll();
    else
        queued = true;
}

void BackgroundInputProcessor::run()
{
    // TODO: do not find when input wasn't changed

    while (_isRunning) {
        emit processingStarted();
        isWaiting = false;
        emit processingFinished(process());
        isWaiting = true;
        if (queued) {
            queued = false;
            continue;
        }

        QMutexLocker locker(&mutex);
        condition.wait(&mutex);
    }
}

QList<QObject*> BackgroundInputProcessor::process()
{
    QString input = lastInput;

    QList<QObject*> result = parser->parse(input);

    for (QObject* item : result)
        item->moveToThread(QGuiApplication::instance()->thread());

    return result;
}

bool BackgroundInputProcessor::isRunning() const
{
    return _isRunning;
}

void BackgroundInputProcessor::setIsRunning(bool isRunning)
{
    _isRunning = isRunning;
    condition.wakeAll();
}

void BackgroundInputProcessor::stop(int waitingTime)
{
    setIsRunning(false);
    if (waitingTime > 0) {
        if (!wait(waitingTime)) {
            terminate();
        }
    }
}
