#include "servicecontainer.h"
#include <iostream>
#include <map>

ServiceContainer ServiceContainer::container;

ServiceContainer::ServiceContainer()
{
}

ServiceContainer::~ServiceContainer()
{
    map<string, IService*>::iterator it;

    for (it = services_.begin(); it != services_.end(); it++) {
        std::cout << "Deleting service " << it->first;
        delete it->second;
    }

    services_.clear();

    std::cout << "Service container destructor" << std::endl << "services length " << services_.size() << std::endl;
}

ServiceContainer& ServiceContainer::sharedContainer()
{
    return container;
}
