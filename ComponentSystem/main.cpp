#include <iostream>
#include "ServiceContainer.h"
#include "DefaultEntityManager.h"
#include "TestComponent.h"
#include "TestSystem.h"

using namespace std;

void registerServices()
{
    ServiceContainer::sharedContainer().registerService("entityManager", new DefaultEntityManager());
}

int main()
{
    registerServices();

    EntityManagerInterface * em = static_cast<EntityManagerInterface *>(ServiceContainer::sharedContainer().getService("entityManager"));

    EntityPtr e = EntityPtr(new Entity());

    for (int i = 0; i < 10; ++i) {
        em->registerEntity(e);
        auto component = new TestComponent();
        em->addComponent(Component(component), e);
    }

    auto components = em->getComponentsWithId("testComponentIdd");

    for_each(components.begin(), components.end(), [](Component c){
        c->info();
    });

    auto system = ComponentSystem(new TestSystem());

    cout << system << endl;

    return 0;
}
