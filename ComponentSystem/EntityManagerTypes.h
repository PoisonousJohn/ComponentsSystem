#ifndef ENTITYMANAGERTYPES_H
#define ENTITYMANAGERTYPES_H

#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace poison {

    class Entity;
    class Component;
    class ComponentSystem;
    
    typedef long unsigned int entityId;
    typedef std::string componentId;
    typedef std::string systemId;
    typedef boost::shared_ptr<Component> SharedComponent;
    typedef boost::shared_ptr<Entity> EntityPtr;
    typedef std::vector< Component* > Components;
    typedef std::vector<EntityPtr> Entities;
    typedef boost::shared_ptr<ComponentSystem> SharedComponentSystem;
    
    
}

#endif // ENTITYMANAGERTYPES_H
