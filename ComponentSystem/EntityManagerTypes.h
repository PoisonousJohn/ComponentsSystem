#ifndef ENTITYMANAGERTYPES_H
#define ENTITYMANAGERTYPES_H

#include <memory>
#include <deque>
#include <vector>
#include <boost/shared_ptr.hpp>

template <typename T1, typename T2>
struct Range {
private:
    std::pair<T1, T2> pair;

public:
    Range(T1 val1, T2 val2) : pair(val1, val2) {}
    T1 start() { return pair.first; }
    T2 end() { return pair.second; }
};

class Entity;
class ComponentInterface;
class ComponentSystemInterface;

typedef long unsigned int entityId;
typedef std::string componentId;
typedef std::string systemId;
typedef std::shared_ptr<ComponentInterface> Component;
typedef Entity* pEntity;
typedef std::vector<Component> Components;
typedef std::vector<pEntity> Entities;
typedef std::shared_ptr<ComponentSystemInterface> ComponentSystem;

#endif // ENTITYMANAGERTYPES_H
