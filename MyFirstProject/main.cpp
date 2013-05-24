#include <iostream>
#include "servicecontainer.h"
#include "defaultentitymanager.h"

using namespace std;

void registerServices()
{
    ServiceContainer::sharedContainer().registerService("entityManager", new DefaultEntityManager());
}

int main()
{
    registerServices();

    IEntityManager* em = static_cast<IEntityManager*>(ServiceContainer::sharedContainer().getService("entityManager"));
    em->registerEntity(new Entity());

    return 0;
}
