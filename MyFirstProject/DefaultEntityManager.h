//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __DefaultEntityManager_H_
#define __DefaultEntityManager_H_

#include <iostream>
#include "EntityManagerInterface.h"
#include "ComponentInterface.h"
#include "ComponentSystemInterface.h"
#include "EntityManagerTypes.h"
#include <unordered_map>
#include <deque>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <memory>


class DefaultEntityManager : public EntityManagerInterface {

    typedef std::unordered_map<entityId, ObjectsHolder<ComponentInterface>> entitiesComponentsMap;

    typedef boost::multi_index::multi_index_container<
        Component,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_non_unique<
//                boost::multi_index::tag<ComponentInterface::componentIdTag>,
                boost::multi_index::const_mem_fun<ComponentInterface, std::string, &ComponentInterface::getId> >
            > // end indexed_by
      > ComponentsIndex;

    ComponentsIndex componentsContainer_;

//    typedef boost::multi_index::multi_index_container<
//        std::,
//        boost::multi_index::indexed_by<
//            boost::multi_index::hashed_unique<
//                boost::multi_index::const_mem_fun<ComponentInterface, std::string, &ComponentInterface::getId()>
//            >
//        >
//    > d;
    std::unordered_map<entityId, pEntity> entities_;
    entitiesComponentsMap entitiesComponents_;
    std::unordered_map<componentId, ObjectsHolder<ComponentInterface>> components_;
    std::unordered_map<systemId, ComponentSystem> systems_;

    long unsigned int lastId;
    long unsigned int maxId;

    long unsigned int generateNewUid();

public:

    DefaultEntityManager();

    ~DefaultEntityManager();

    virtual void registerEntity(pEntity entity);
    virtual void removeEntity(pEntity entity);

    virtual void addComponent(Component component, pEntity entity);
    virtual void removeComponent(componentId id, pEntity entity);

    virtual void registerSystem(systemId id, ComponentSystemInterface * system);

    virtual Component getComponent(componentId id, pEntity entity);
    virtual Objects<Component> getComponentsForEntity(pEntity entity);
    virtual Objects<Component> getComponentsWithId(componentId id);
    virtual ComponentSystemInterface * getSystem(systemId id);

    virtual void removeAllEntities();
};


#endif //__DefaultEntityManager_H_
