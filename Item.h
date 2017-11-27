#ifndef ITEM_H
#define ITEM_H

#include <QIcon>
#include <QObject>

class Item : public QObject {
    Q_OBJECT

    Q_PROPERTY(QIcon icon READ getIcon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString moduleName READ getModuleName WRITE setModuleName NOTIFY moduleNameChanged)
    Q_PROPERTY(ITEM_TYPE type READ getType)
    Q_PROPERTY(bool smartyShouldBeClosed READ getSmartyShouldBeClosed)

public:
    enum ITEM_TYPE {
        ITEM,
        TEXT_ITEM
    };
    Q_ENUM(ITEM_TYPE);

    explicit Item(const QIcon& icon = QIcon(), QObject* parent = nullptr);

    QIcon getIcon() const;
    void setIcon(const QIcon& value);

    QString getModuleName() const;
    void setModuleName(const QString& value);

    // this will be executed when user press enter on item from list view
    Q_INVOKABLE virtual void action();

    Item::ITEM_TYPE getType() const;

    bool getSmartyShouldBeClosed() const;

signals:
    void moduleNameChanged(const QString& moduleName);
    void iconChanged(const QIcon& icon);

public slots:

protected:
    ITEM_TYPE type;
    QIcon icon;
    QString moduleName;
    // this flag indicates that Smarty should be closed after execution
    // action (It may not happen if user disabled such behaviour in settings)
    bool smartyShouldBeClosed = true;
};

#endif // ITEM_H
