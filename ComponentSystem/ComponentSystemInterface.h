#ifndef ICOMPONENTSYSTEM_H
#define ICOMPONENTSYSTEM_H

#include <iostream>
#include <string>

class ComponentSystemInterface
{
public:
    ComponentSystemInterface();
    virtual ~ComponentSystemInterface() {}
    virtual std::string info() const = 0;
};

std::ostream& operator <<(std::ostream& ostream, const ComponentSystemInterface& component);

#endif // ICOMPONENTSYSTEM_H
