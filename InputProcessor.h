#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include "BackgroundInputProcessor.h"

#include <QKeyEvent>
#include <QObject>
#include <QtCore>
#include <QtGui>

class InputProcessor : public QObject {
    Q_OBJECT
public:
    explicit InputProcessor(QObject* parent = nullptr);
    virtual ~InputProcessor();

signals:
    void processingStarted();
    void processingFinished(const QList<QObject*>& items);

public slots:
    void processInput(const QString& input);
    bool processKey(Qt::Key key);
    void threadFinished(QList<QObject*> items);

private:
    QString lastInput;
    BackgroundInputProcessor* thread = nullptr;
};

#endif // INPUTPROCESSOR_H
