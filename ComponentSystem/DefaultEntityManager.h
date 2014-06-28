//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __DefaultEntityManager_H_
#define __DefaultEntityManager_H_

#include <iostream>
#include <thread>
#include <memory>
#include <unordered_map>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <ComponentSystem/EntityManager.h>
#include <ComponentSystem/Component.h>
#include <ComponentSystem/ComponentSystem.h>
#include <ComponentSystem/EntityManagerTypes.h>

namespace poison {
    
    class DefaultEntityManager : public poison::EntityManager {

    public:

        DefaultEntityManager();

        ~DefaultEntityManager();

        void registerEntity(Entity* entity) override;
        
        void removeEntity(Entity* entity) override;

        void addComponent(const componentId& id, SharedComponent& component, Entity* entity) override;
        
        void removeComponent(const componentId& id, Entity* entity) override;

        void removeComponent(const componentId& id, entityId entityId) override;

        void registerSystem(const systemId& id, ComponentSystem* system) override;

        SharedComponent getComponent(const componentId& id, const Entity* entity) const override;
        
        Components getComponentsForEntity(Entity* entity) override;
        
        Components getComponentsWithId(const componentId& id) override;
        
        SharedComponentSystem getSystem(systemId id) override;

        void removeAllEntities() override;
        
        EntityPtr getEntity(entityId id) override;
        
        void printDebugInfo() const override;
        
        void update(float dt) override;

        void pauseAllSystems() override;

        void stopAllSystems() override;

        void runAllSystems() override;
        
        void registerForUpdate(Entity* entity) override;
       
        void removeFromUpdate(Entity* entity) override;

        
    protected:

        typedef boost::multi_index::multi_index_container<
            SharedComponent,
            boost::multi_index::indexed_by<
                boost::multi_index::hashed_non_unique<
                    boost::multi_index::tag<Component::byComponentIdTag>,
                    boost::multi_index::const_mem_fun<Component, const std::string&, &Component::getComponentId>
                >,
                boost::multi_index::hashed_non_unique<
                    boost::multi_index::tag<Component::byEntityIdTag>,
                    boost::multi_index::const_mem_fun<Component, entityId, &Component::getEntityId>
                >,
                boost::multi_index::hashed_non_unique<
                    boost::multi_index::tag<Component::byComponentAndEntityIdTag>,
                    boost::multi_index::composite_key<
                        Component,
                        boost::multi_index::const_mem_fun<Component, const std::string&, &Component::getComponentId>,
                        boost::multi_index::const_mem_fun<Component, entityId, &Component::getEntityId>
                    >
                >
            >
        > ComponentsIndex;

        ComponentsIndex componentsContainer_;

        std::unordered_map<entityId, EntityPtr> entities;
        
        std::unordered_map<systemId, SharedComponentSystem> systems;
        
        std::set< Entity* > entitiesToUpdate;

        long unsigned int lastId;
        
        long unsigned int maxId;

        mutable std::recursive_mutex mutex ;
        
        long unsigned int generateNewUid();
    };
    
}



#endif //__DefaultEntityManager_H_
