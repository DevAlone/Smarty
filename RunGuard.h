#ifndef RUNGUARD_H
#define RUNGUARD_H

#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

class RunGuard {
public:
    RunGuard(const QString& key);
    virtual ~RunGuard();

    bool isRunning();
    bool tryToRun();
    void release();

private:
    const QString key;
    const QString memLockKey;
    const QString sharedMemKey;

    QSharedMemory sharedMemory;
    QSystemSemaphore memLock;

    Q_DISABLE_COPY(RunGuard);
};

#endif // RUNGUARD_H
