//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __DefaultEntityManager_H_
#define __DefaultEntityManager_H_

#include <iostream>
#include "EntityManagerInterface.h"
#include "ComponentInterface.h"
#include "ComponentSystemInterface.h"
#include <map>
#include <deque>

using namespace std;


class DefaultEntityManager : public EntityManagerInterface {

    typedef deque<Component> componentsContainer;
    typedef map<entityId, componentsContainer > componentsByEidMap;
    typedef pair<entityId, componentsContainer > componentsByEidMapPair;
    typedef pair<componentId, componentsByEidMap > componentsByEidPair;

    map<entityId, pEntity> entities_;
    map<componentId,
        componentsByEidMap
    > components_;
    componentsByEidMap componentsByEid_;

    map<systemId, ComponentSystem> systems_;

    long unsigned int lastId;
    long unsigned int maxId;

    long unsigned int generateNewUid();

public:

    DefaultEntityManager();

    ~DefaultEntityManager();

    virtual void registerEntity(Entity *entity);

    virtual void removeAllEntities();

    virtual void removeEntity(pEntity entity);


    virtual void removeComponent(componentId id, pEntity entity);

    virtual void registerSystem(systemId id, ComponentSystemInterface *system);

    virtual Component getComponent(componentId id, pEntity entity);


    virtual ComponentSystemInterface *getSystem(systemId id);
};


#endif //__DefaultEntityManager_H_
