#ifndef BACKGROUNDINPUTPROCESSOR_H
#define BACKGROUNDINPUTPROCESSOR_H

#include "InputParser.h"
#include "Item.h"

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <atomic>

class BackgroundInputProcessor : public QThread {
    Q_OBJECT
public:
    explicit BackgroundInputProcessor(QObject* parent = nullptr);

    void processInput(const QString& input);

    bool isRunning() const;
    void setIsRunning(bool isRunning);
    void stop(int waitingTime = 0);

signals:
    void processingStarted();
    void processingFinished(QList<QObject*> items);

public slots:

protected:
    virtual void run();

private:
    QList<QObject*> process();

    InputParser* parser = nullptr;
    bool _isRunning = true;
    QWaitCondition condition;
    QMutex mutex;
    QString lastInput;
    bool queued = false;
    std::atomic<bool> isWaiting;
};

#endif // BACKGROUNDINPUTPROCESSOR_H
