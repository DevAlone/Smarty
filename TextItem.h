#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "Item.h"

class TextItem : public Item {
    Q_OBJECT

    Q_PROPERTY(QString data READ getData WRITE setData NOTIFY dataChanged)
public:
    TextItem(const QString& data, QObject* parent = nullptr);

    QString getData() const;
    void setData(const QString& value);

signals:
    void dataChanged(const QString& data);

protected:
    QString data;
};

#endif // TEXTITEM_H
