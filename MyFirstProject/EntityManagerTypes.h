#ifndef ENTITYMANAGERTYPES_H
#define ENTITYMANAGERTYPES_H

#include <memory>
#include <boost/shared_ptr.hpp>

class Entity;
class ComponentInterface;
class ComponentSystemInterface;

typedef long unsigned int entityId;
typedef std::string componentId;
typedef std::string systemId;
typedef boost::shared_ptr<ComponentInterface> Component;
typedef Entity* pEntity;
typedef std::shared_ptr<ComponentSystemInterface> ComponentSystem;

#endif // ENTITYMANAGERTYPES_H
