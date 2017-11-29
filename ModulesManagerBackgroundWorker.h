#ifndef MODULESMANAGERBACKGROUNDWORKER_H
#define MODULESMANAGERBACKGROUNDWORKER_H

#include <QObject>
#include <QThread>

class ModulesManagerBackgroundWorker : public QThread {
    Q_OBJECT
public:
    explicit ModulesManagerBackgroundWorker(QObject* parent = nullptr);

protected:
    virtual void run();

signals:

public slots:
};

#endif // MODULESMANAGERBACKGROUNDWORKER_H
