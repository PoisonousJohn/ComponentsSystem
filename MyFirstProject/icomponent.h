#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>

class IComponent
{
public:
    IComponent();
    virtual std::string getId() = 0;
    virtual void info() = 0;
    virtual ~IComponent();
};

#endif // ICOMPONENT_H
