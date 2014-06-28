#ifndef ICOMPONENTSYSTEM_H
#define ICOMPONENTSYSTEM_H

#include <boost/signals2.hpp>
#include <ComponentSystem/EntityManager.h>

namespace poison {
    
    class ComponentSystem {
    protected:
        bool enabled;
    public:
        ComponentSystem() : enabled(true) {}
        
        boost::signals2::signal<void(bool)> enabledStateChanged;
        
        virtual ~ComponentSystem() {}
        
        EntityManager* getEntityManager() {
            return EntityManager::instance();
        }
        
        virtual void update(float deltaTime) {}
        
        virtual void pause() { enabled = !enabled; }
        
        virtual void setEnabled(bool enabled);
        
        virtual bool isEnabled() { return enabled; }
        
        static std::string getId() { return ""; }
    };
    
}


#endif // ICOMPONENTSYSTEM_H
