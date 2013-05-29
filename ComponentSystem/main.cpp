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

    EntityManagerInterface * em = static_cast<EntityManagerInterface *>(ServiceContainer::sharedContainer().getService("entityManager"));

    Entity* e = new Entity();
    em->registerEntity(e);
    auto component = new TestComponent();

    em->addComponent(Component(component), e);
    auto c = em->getComponent(component->getId(), e);

    return 0;
}
