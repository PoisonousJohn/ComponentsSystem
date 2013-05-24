//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __DefaultEntityManager_H_
#define __DefaultEntityManager_H_

#include <iostream>
#import "IEntityManager.h"
#include "icomponent.h"
#include <map>

using namespace std;


class DefaultEntityManager : public IEntityManager {

    map<int, Entity*> entities_;
    map<string, IComponent*> components_;
    map<string, IComponent*> componentsByEid_;
    map<string, IComponent*> systems_;
    long unsigned int lastId;
    long unsigned int maxId;

    long unsigned int generateNewUid();

public:

    DefaultEntityManager();

    ~DefaultEntityManager();

    virtual void registerEntity(Entity *entity);

    virtual void removeEntity(Entity *entity);

    virtual void addComponent(IComponent *component, Entity *entity);

    virtual void removeComponent(string id, Entity *entity);

    virtual IComponent *getComponent(string id, Entity *entity);

    virtual vector<IComponent *> getComponentsForEntity(Entity *entity);

    virtual vector<Entity *> getEntitiesWithComponent(string id);

    virtual void registerSystem(string id, IComponentSystem *system);

    virtual IComponentSystem *getSystem(string id);

    virtual void removeAllEntities();
};


#endif //__DefaultEntityManager_H_
