//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __IEntityManager_H_
#define __IEntityManager_H_

#include <iostream>
#include "icomponent.h"
#include "icomponentsystem.h"
#include "entity.h"
#include <vector>

using namespace std;


class IEntityManager {
public:
    virtual void registerEntity(Entity* entity) = 0;
    virtual void removeEntity(Entity* entity) = 0;
    virtual void addComponent(IComponent* component, Entity* entity) = 0;
    virtual void removeComponent(string id, Entity* entity) = 0;
    virtual IComponent* getComponent(string id, Entity* entity) = 0;
    virtual vector<IComponent *> getComponentsForEntity(Entity* entity) = 0;
    virtual vector<Entity *> getEntitiesWithComponent(string id) = 0;
    virtual void registerSystem(string id, IComponentSystem* system) = 0;
    virtual IComponentSystem* getSystem(string id) = 0;
    virtual void removeAllEntities() = 0;
};


#endif //__IEntityManager_H_
