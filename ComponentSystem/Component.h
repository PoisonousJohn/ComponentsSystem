#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>
#include <thread>
#include <ComponentSystem/EntityManager.h>
#include <ComponentSystem/EntityManagerTypes.h>

namespace poison {
    
    class Component {
        
    public:
        Component() = delete;
        virtual ~Component() {
            //        std::cout << "removed component " << this << " for entity " << eid_ << " thread " << std::this_thread::get_id() << std::endl;
        }
        //    virtual ~Component() { std::cout << "~Component " << ": #" << getEntityId(); }
        
        // multi_index tags
        struct byComponentIdTag {};
        struct byEntityIdTag {};
        struct byComponentAndEntityIdTag{};
        
        
        
        entityId getEntityId() const { return eid_; }
        virtual void setEntityId(const entityId eid) { eid_ = eid; }
        
        void setRemoved(bool value) { removed = value; }
        /**
         * @brief use this function when iteration over elements that can be deleted in loop to check whether it was deleted
         */
        bool isRemoved() { return removed; }
        
        const std::string& getComponentId() const { return *id; }
        
        /**
         * @brief this method should be overriden
         **/
        static std::string geId() { return ""; }
        
        template <typename T, typename ... Args>
        static T* create(Args ... args) {
            return new T(T::getId(), args...);
        }
        
    protected:
        Component( const std::string* _id )
        : eid_(0)
        , removed(false)
        , id(_id)
        {
            assert(id != 0 && !id->empty() && "error");
        }
        
        entityId eid_;
        const std::string* id;
        bool removed;
    };
    
}


#endif // ICOMPONENT_H
