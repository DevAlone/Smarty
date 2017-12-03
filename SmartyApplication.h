#ifndef SMARTYAPPLICATION_H
#define SMARTYAPPLICATION_H

#include <QGuiApplication>
#include <QObject>

class SmartyApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit SmartyApplication(int& argc, char** argv);

signals:

public slots:
    Q_INVOKABLE void close();
};

#endif // SMARTYAPPLICATION_H
