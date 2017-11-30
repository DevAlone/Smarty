#include "Module.h"

namespace smart_modules {
Module::~Module()
{
}

Module::Module()
{
}

int Module::getPriority() const
{
    return priority;
}
}
