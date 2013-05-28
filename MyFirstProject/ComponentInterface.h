#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

class ComponentInterface
{
public:
    ComponentInterface();
    virtual std::string getId() = 0;
    virtual void info() = 0;
    virtual ~ComponentInterface();
};

#endif // ICOMPONENT_H
