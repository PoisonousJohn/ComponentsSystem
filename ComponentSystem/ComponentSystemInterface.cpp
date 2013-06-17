#include "ComponentSystemInterface.h"

ComponentSystemInterface::ComponentSystemInterface()
{
}

std::ostream& operator <<(std::ostream& ostream, const ComponentSystemInterface& component)
{
    ostream << component.info();
    return ostream;
}
