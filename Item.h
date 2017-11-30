#ifndef ITEM_H
#define ITEM_H

#include <QIcon>
#include <QObject>

namespace smart_modules {
class Module;
}

class Item : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString iconPath READ getIconPath WRITE setIconPath NOTIFY iconPathChanged)
    Q_PROPERTY(QString moduleName READ getModuleName CONSTANT) // WRITE setModuleName NOTIFY moduleNameChanged)
    Q_PROPERTY(ITEM_TYPE type READ getType)
    Q_PROPERTY(bool smartyShouldBeClosed READ getSmartyShouldBeClosed)
    Q_PROPERTY(int priority READ getPriority CONSTANT)
    Q_PROPERTY(QString renderer READ getRenderer CONSTANT)

public:
    enum ITEM_TYPE {
        ITEM,
        TEXT_ITEM
    };
    Q_ENUM(ITEM_TYPE);

    explicit Item(smart_modules::Module* module = nullptr, QObject* parent = nullptr);

    QString getModuleName() const;

    // this will be executed when user press enter on item from list view
    Q_INVOKABLE virtual void action();

    Item::ITEM_TYPE getType() const;

    bool getSmartyShouldBeClosed() const;

    QString getIconPath() const;
    void setIconPath(const QString& value);

    int getPriority() const;

    bool operator<(const Item& other);

    void setPriority(int value);

    QString getRenderer() const;

signals:
    // void moduleNameChanged(const QString& moduleName);
    void iconPathChanged(const QString& iconPath);

public slots:

protected:
    ITEM_TYPE type;
    QString iconPath;
    smart_modules::Module* module = nullptr;
    // QString moduleName;
    // this flag indicates that Smarty should be closed after execution
    // action (It may not happen if user disabled such behaviour in settings)
    bool smartyShouldBeClosed = true;
    int priority = 0;

    QString renderer = "ItemRenderer";
};

#endif // ITEM_H
