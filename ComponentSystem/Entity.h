#ifndef ENTITY_H
#define ENTITY_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/pointer_cast.hpp>
#include <ComponentSystem/EntityManager.h>
#include <ComponentSystem/Component.h>

namespace poison {
    
    class Entity {
        
    public:
        Entity() : id(0), removed(false) {
            getEntityManager()->registerEntity(this);
        }
        
        virtual ~Entity() {
            getEntityManager()->removeFromUpdate(this);
        }
        
        void setId(entityId id) {
            this->id = id;
        }
        
        entityId getId() const {
            return this->id;
        }
        
        virtual void update(float dt) {};
        
        // get component of type T
        template <typename T>
        T* getComponent() {
            return dynamic_cast<T*>(getEntityManager()->getComponent(*T::getId(), this).get());
        }
        
        template <typename T, typename ... Args>
        T* addComponent(Args ... args) {
            auto obj = Component::create<T>( args... );
//            auto ptr = boost::shared_ptr<T>( obj );
            auto ptr = boost::shared_ptr<Component>( obj );
//            auto component = boost::dynamic_pointer_cast<Component>( ptr );
            getEntityManager()->addComponent(*T::getId(), ptr, this);
            
            return obj;
        }
        
        template <typename T>
        void removeComponent() {
            getEntityManager()->removeComponent(*T::getId(), this);
        }
        
        template <typename T = Entity>
        boost::shared_ptr<T> getSharedPtr() {
            return boost::static_pointer_cast<T>(getEntityManager()->getEntity(id));
        }
        
        /**
         * @brief remove entity from entity manager
         */
        virtual void remove() {
            if ( getEntityManager() != NULL )
                getEntityManager()->removeEntity(this);
        }
        
        void setRemoved(bool value) { removed = value; }
        
        bool isRemoved() const { return removed; }
        
    protected:
        entityId id;
        bool removed;
        
        EntityManager* getEntityManager() const {
            static EntityManager* em = EntityManager::instance();
            return em;
        }
    };
    
}


#endif // ENTITY_H
