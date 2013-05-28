#include "ServiceContainer.h"
#include <iostream>

ServiceContainer ServiceContainer::container;

ServiceContainer::ServiceContainer()
{
}

ServiceContainer::~ServiceContainer()
{
    map<string, ServiceInterface *>::iterator it;

    for (it = services_.begin(); it != services_.end(); it++) {
        std::cout << "Deleting service " << it->first << std::endl;
        delete it->second;
    }

    services_.clear();

    std::cout << "Service container destructor" << std::endl << "services length " << services_.size() << std::endl;
}

ServiceContainer& ServiceContainer::sharedContainer()
{
    return container;
}
