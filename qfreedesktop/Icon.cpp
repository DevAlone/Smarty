#include "Icon.h"

namespace qfreedesktop {
Icon::Icon(const QString& path)
    : path(path)
{
}

Icon& Icon::operator=(const Icon& obj)
{
    type = obj.type;
    size = obj.size;
    context = obj.context;
    themeName = obj.themeName;
}
}
