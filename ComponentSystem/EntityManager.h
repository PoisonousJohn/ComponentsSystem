//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.





#ifndef __IEntityManager_H_
#define __IEntityManager_H_

#include <ServiceContainer/ServiceInterface.h>
#include <ComponentSystem/EntityManagerTypes.h>

namespace poison {

    const std::string kEntityManagerService = "kEntityManagerService";


    class EntityManager : public ServiceInterface {
    public:
        
        virtual void registerEntity(Entity* entity) = 0;
        
        virtual void removeEntity(Entity* entity) = 0;
        
        virtual void addComponent(const componentId& id, SharedComponent& component, Entity* entity) = 0;
        
        //    template <typename T>
        //    void removeComponent();
        
        virtual void removeComponent(const componentId& id, Entity* entity) = 0;
        
        virtual void removeComponent(const componentId& id, entityId entityId) = 0;
        
        template <typename T, typename ... Args>
        void registerSystem(Args ... args) {
            registerSystem( *T::getId(), new T(args...) );
        }
        
        virtual void registerSystem(const systemId& id, ComponentSystem* system) = 0;
        
        virtual SharedComponent getComponent(const componentId& id, const Entity* entity) const = 0;
        
        template <typename T>
        T* getComponent(const Entity* entity) const {
            return dynamic_cast<T*>( getComponent(*T::getId(), entity).get() );
        }
        
        virtual Components getComponentsForEntity(Entity* entity) = 0;
        
        template <typename T>
        Components getComponents() {
            auto componentId = T::getId();
            return std::move( getComponentsWithId( *componentId ) );
        }
        
        virtual Components getComponentsWithId(const componentId& id) = 0;
        
        template <typename T>
        boost::shared_ptr< T > getSystem() {
            return boost::dynamic_pointer_cast< T >( getSystem( *T::getId() ) );
        }
        
        virtual SharedComponentSystem getSystem(systemId id) = 0;
        
        virtual void removeAllEntities() = 0;
        
        virtual EntityPtr getEntity(entityId id) = 0;
        
        virtual void printDebugInfo() const = 0;
        
        virtual void update(float dt) = 0;
        
        virtual void pauseAllSystems() = 0;
        
        virtual void stopAllSystems() = 0;
        
        virtual void runAllSystems() = 0;
        
        virtual void registerForUpdate(Entity* entity) = 0;
        
        virtual void removeFromUpdate(Entity* entity) = 0;
        
        SERVICE_INSTANCE(EntityManager)
        
        static std::string getId() { return kEntityManagerService; }
    };
    
}


#endif //__IEntityManager_H_
