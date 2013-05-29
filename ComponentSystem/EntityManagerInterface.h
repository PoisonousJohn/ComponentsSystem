//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __IEntityManager_H_
#define __IEntityManager_H_

#include <memory>
#include <iostream>
#include <list>
#include <deque>
#include "ComponentInterface.h"
#include "ComponentSystemInterface.h"
#include "Entity.h"
#include "ServiceInterface.h"
#include "ObjectsHolder.h"
#include "EntityManagerTypes.h"


class EntityManagerInterface : public ServiceInterface {
public:

    virtual void registerEntity(pEntity entity) = 0;
    virtual void removeEntity(pEntity entity) = 0;

    virtual void addComponent(Component component, pEntity entity) = 0;
    virtual void removeComponent(componentId id, pEntity entity) = 0;

    virtual void registerSystem(systemId id, ComponentSystemInterface * system) = 0;

    virtual Component getComponent(componentId id, pEntity entity) = 0;
    virtual Objects<Component> getComponentsForEntity(pEntity entity) = 0;
    virtual Objects<Component> getComponentsWithId(componentId id) = 0;
    virtual ComponentSystemInterface * getSystem(systemId id) = 0;

    virtual void removeAllEntities() = 0;
};


#endif //__IEntityManager_H_
