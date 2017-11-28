#include "ImageProvider.h"

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap ImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    QPixmap result(id);

    *size = result.size();

    if (requestedSize.isValid())
        return result.scaled(requestedSize);
    else
        return result;
}
