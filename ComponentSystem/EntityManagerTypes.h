#ifndef ENTITYMANAGERTYPES_H
#define ENTITYMANAGERTYPES_H

#include <memory>
#include <deque>
#include <vector>
#include <boost/shared_ptr.hpp>

class Entity;
class ComponentInterface;
class ComponentSystemInterface;

typedef long unsigned int entityId;
typedef std::string componentId;
typedef std::string systemId;
typedef std::shared_ptr<ComponentInterface> Component;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::vector<Component> Components;
typedef std::vector<EntityPtr> Entities;
typedef std::shared_ptr<ComponentSystemInterface> ComponentSystem;

#endif // ENTITYMANAGERTYPES_H
