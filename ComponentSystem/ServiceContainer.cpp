#include "ServiceContainer.h"
#include <iostream>

ServiceContainer ServiceContainer::container;

ServiceContainer::ServiceContainer()
{
}

ServiceContainer::~ServiceContainer()
{

}

ServiceContainer& ServiceContainer::sharedContainer()
{
    return container;
}
