#ifndef ITEM_H
#define ITEM_H

#include <QIcon>
#include <QObject>

class Item : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString iconPath READ getIconPath WRITE setIconPath NOTIFY iconPathChanged)
    Q_PROPERTY(QString moduleName READ getModuleName WRITE setModuleName NOTIFY moduleNameChanged)
    Q_PROPERTY(ITEM_TYPE type READ getType)
    Q_PROPERTY(bool smartyShouldBeClosed READ getSmartyShouldBeClosed)

public:
    enum ITEM_TYPE {
        ITEM,
        TEXT_ITEM
    };
    Q_ENUM(ITEM_TYPE);

    explicit Item(QObject* parent = nullptr);

    QString getModuleName() const;
    void setModuleName(const QString& value);

    // this will be executed when user press enter on item from list view
    Q_INVOKABLE virtual void action();

    Item::ITEM_TYPE getType() const;

    bool getSmartyShouldBeClosed() const;

    QString getIconPath() const;
    void setIconPath(const QString& value);

signals:
    void moduleNameChanged(const QString& moduleName);
    void iconPathChanged(const QString& iconPath);

public slots:

protected:
    ITEM_TYPE type;
    QString iconPath;
    QString moduleName;
    // this flag indicates that Smarty should be closed after execution
    // action (It may not happen if user disabled such behaviour in settings)
    bool smartyShouldBeClosed = true;
};

#endif // ITEM_H
