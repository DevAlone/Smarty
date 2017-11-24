#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item : public QObject {
    Q_OBJECT
public:
    explicit Item(QObject* parent = nullptr);

    QString getData() const;
    void setData(const QString& value);

signals:

public slots:

private:
    // TODO: add icon
    QString data;
};

#endif // ITEM_H
