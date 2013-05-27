#include <iostream>
#include "ServiceContainer.h"
#include "DefaultEntityManager.h"
#include "TestComponent.h"

using namespace std;

void registerServices()
{
    ServiceContainer::sharedContainer().registerService("entityManager", new DefaultEntityManager());
}

int main()
{
    registerServices();

    IEntityManager* em = static_cast<IEntityManager*>(ServiceContainer::sharedContainer().getService("entityManager"));

    Entity* e = new Entity();
    em->registerEntity(e);
    em->addComponent(pIComponent(new TestComponent), e);

    return 0;
}
