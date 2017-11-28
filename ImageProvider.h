#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider {
public:
    explicit ImageProvider();

    virtual QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);
signals:

public slots:
};

#endif // IMAGEPROVIDER_H
