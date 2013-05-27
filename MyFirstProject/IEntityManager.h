//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __IEntityManager_H_
#define __IEntityManager_H_

#include <iostream>
#include <list>
#include <deque>
#include "IComponent.h"
#include "IComponentSystem.h"
#include "Entity.h"
#include "IService.h"

using namespace std;

typedef long unsigned int entityId;
typedef string componentId;
typedef shared_ptr<IComponent> pIComponent;
typedef Entity* pEntity;
typedef shared_ptr<IComponentSystem> pIComponentSystem;
typedef string systemId;
// start-end iterators pairs types
typedef pair<deque<pIComponent>::const_iterator,deque<pIComponent>::const_iterator> Components;
typedef pair<deque<pEntity>::const_iterator,deque<pEntity>::const_iterator> Entities;

class IEntityManager : public IService {
public:

    virtual void registerEntity(pEntity entity) = 0;
    virtual void removeEntity(pEntity entity) = 0;
    virtual void addComponent(pIComponent component, pEntity entity) = 0;
    virtual void removeComponent(componentId id, pEntity entity) = 0;

    virtual void registerSystem(systemId id, IComponentSystem* system) = 0;

    virtual pIComponent getComponent(componentId id, pEntity entity) = 0;
    virtual Components getComponentsForEntity(pEntity entity) = 0;
    virtual Entities getEntitiesWithComponent(componentId id) = 0;
    virtual IComponentSystem* getSystem(systemId id) = 0;

    virtual void removeAllEntities() = 0;
};


#endif //__IEntityManager_H_
