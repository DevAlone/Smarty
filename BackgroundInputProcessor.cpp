#include "BackgroundInputProcessor.h"

#include <QGuiApplication>
#include <iostream>

BackgroundInputProcessor::BackgroundInputProcessor(QObject* parent)
    : QThread(parent)
{
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
    std::cout << "thread is working: " << input.toStdString() << std::endl;
    int a;
    for (size_t i = 0; i < 1000000; ++i)
        a += rand();
    std::cout << "rand is: " << a << std::endl;
    //    if (input.size() < 1)
    //        return QList<Item*>();

    QList<QObject*> result;

    if (input.size()) {
        result.append(new Item(input, "input module"));
        for (size_t i = 0; i < 2; ++i) {
            auto text = QString("test data") + QString::number(i);
            auto moduleName = "test module";
            Item* item = new Item(text, moduleName);
            result.append(item);
        }
    }

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
