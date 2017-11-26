#ifndef ITEM_H
#define ITEM_H

#include <QIcon>
#include <QObject>

class Item : public QObject {
    Q_OBJECT

    Q_PROPERTY(QIcon icon READ getIcon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString data READ getData WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QString moduleName READ getModuleName WRITE setModuleName NOTIFY moduleNameChanged)
public:
    explicit Item(const QString& data, const QIcon& icon = QIcon(), QObject* parent = nullptr);

    QString getData() const;
    void setData(const QString& value);

    QIcon getIcon() const;
    void setIcon(const QIcon& value);

    QString getModuleName() const;
    void setModuleName(const QString& value);

    // this will be executed when user press enter on item from list view
    Q_INVOKABLE virtual void action();

signals:
    void dataChanged(const QString& data);
    void moduleNameChanged(const QString& moduleName);
    void iconChanged(const QIcon& icon);

public slots:

protected:
    QIcon icon;
    QString data;
    QString moduleName;
    // this flag indicates that Smarty should be closed after execution
    // action (It may not happen if user disabled such behaviour in settings)
    bool closesProgram = true;
};

#endif // ITEM_H
