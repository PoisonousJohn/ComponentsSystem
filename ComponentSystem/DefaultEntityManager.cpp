//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.




#include <limits>
#include <algorithm>
#include "DefaultEntityManager.h"
#include "EntityManagerException.h"
#include "Entity.h"

using namespace std;

poison::DefaultEntityManager::DefaultEntityManager() {
    lastId = 1;
    maxId = numeric_limits<unsigned>::max();
}

poison::DefaultEntityManager::~DefaultEntityManager() {

    removeAllEntities();

    systems.clear();

    cout << "entities count " << entities.size() << endl;
    
    cout << "destructor: default entity manager" << endl;
}

unsigned long poison::DefaultEntityManager::generateNewUid() {
    if (lastId < maxId) {
        return lastId++;
    } else {
        cout << "failed to assign new uid to entity" << endl;
        throw EntityManagerException();
    }
}

void poison::DefaultEntityManager::registerEntity(Entity* entity) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    if (!entity->getId()) {
        entity->setId(generateNewUid());
        entities.insert(std::make_pair(entity->getId(), boost::shared_ptr<Entity>(entity)));
    }
}

void poison::DefaultEntityManager::removeAllEntities() {
    componentsContainer_.clear();
    entities.clear();
}

void poison::DefaultEntityManager::addComponent(const componentId& id, poison::SharedComponent& component, Entity* entity) {
    std::lock_guard<std::recursive_mutex> lock(mutex);

    component->setEntityId(entity->getId());
//    std::cout << "adding component " << component << " thread " << std::this_thread::get_id() << std::endl;
    componentsContainer_.insert(component);

}

poison::SharedComponent poison::DefaultEntityManager::getComponent(const componentId& id, const Entity* entity) const {
    std::lock_guard<std::recursive_mutex> lock(mutex);

    auto componentIt = componentsContainer_.get<Component::byComponentAndEntityIdTag>().find(boost::tuples::make_tuple(id, entity->getId()));
    auto endIt = componentsContainer_.get<Component::byComponentAndEntityIdTag>().end();

    if (componentIt != endIt) {
        return *componentIt;
    }

//    std::cout << "Component not found" << std::endl;
//    printDebugInfo();
//    throw EntityManagerException();
    return SharedComponent();
}

void poison::DefaultEntityManager::removeEntity(Entity* entity) {
#ifdef DEBUG
    assert(entity->getId() < 1000000 && "wrong entity");
#endif
    entity->setRemoved(true);
    ComponentsIndex::index<Component::byEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<Component::byEntityIdTag>().equal_range(entity->getId());
//    std::cout << "\n\n\n\n removing entity " << entity->getId() << std::endl;
    auto it = first;
    while ( it != last) {
        auto component = *it;
        component->setRemoved(true);
        ++it;
    }
//    std::cout << "entity components: \n";

//    for (auto it = first; it != last; ++it) {
//        auto component = (*it);
//        std::cout << "component with eid " << component->getEntityId() << " " << component->getId() << std::endl;
//    }

    componentsContainer_.get<Component::byEntityIdTag>().erase(first, last);
    entities.erase(entity->getId());

//    printDebugInfo();
}

void poison::DefaultEntityManager::removeComponent(const componentId& id, entityId entityId) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    ComponentsIndex::index<Component::byComponentAndEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<Component::byComponentAndEntityIdTag>().equal_range(boost::tuples::make_tuple(id, entityId));
    auto it = first;
    while ( it != last) {
        auto component = *it;
        component->setRemoved(true);
        ++it;
    }
    componentsContainer_.get<Component::byComponentAndEntityIdTag>().erase(first, last);
}

void poison::DefaultEntityManager::removeComponent(const componentId& id, Entity* entity) {
    removeComponent(id, entity->getId());
    auto component = getComponent(id, entity);
    if (component)
        component->setRemoved(true);
}

void poison::DefaultEntityManager::registerSystem(const systemId& id, ComponentSystem* system) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    systems.insert(std::make_pair(id, boost::shared_ptr<ComponentSystem>(system)));
}

poison::SharedComponentSystem poison::DefaultEntityManager::getSystem(systemId id) {
    auto system = systems.find(id);

    assert(system != systems.end() && "System not found");


    return system->second;
}

poison::Components poison::DefaultEntityManager::getComponentsForEntity(Entity* entity) {
    ComponentsIndex::index<Component::byEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<Component::byEntityIdTag>().equal_range(entity->getId());
    Components components;
    
    if (first != componentsContainer_.get<Component::byEntityIdTag>().end()) {
        
        auto size = std::distance(first, last);
        components.reserve(size);
        for (auto it = first; it != last; ++it) {
            components.push_back( (*it).get() );
        }
    }
    
    return components;
}
poison::Components poison::DefaultEntityManager::getComponentsWithId(const componentId& id) {
    ComponentsIndex::index<Component::byComponentIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<Component::byComponentIdTag>().equal_range(id);
    
    Components components;
    
    if (first != componentsContainer_.get<Component::byComponentIdTag>().end()) {
        
        auto size = std::distance(first, last);
        components.reserve(size);
        for (auto it = first; it != last; ++it) {
            components.push_back( (*it).get() );
        }
    }
    
    return components;
}

poison::EntityPtr poison::DefaultEntityManager::getEntity(entityId id) {
    auto entity = entities.find(id);
    
    if (entity == entities.end()) {
        std::cout << "Entity " << id << " not found";
        printDebugInfo();
        throw EntityManagerException();
    }
    
    return entity->second;
}

void poison::DefaultEntityManager::printDebugInfo() const {
    std::cout << "ENTITY MANAGER CONTAINS:" << std::endl;

    for (auto pair : entities) {
        std::cout << "entity " << pair.first << std::endl;
    }
    
    std::cout << std::endl;
}

void poison::DefaultEntityManager::pauseAllSystems() {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    for (auto system : systems) {
        system.second->pause();
    }
}

void poison::DefaultEntityManager::stopAllSystems() {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    for (auto system : systems) {
        system.second->setEnabled(false);
    }
}

void poison::DefaultEntityManager::runAllSystems() {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    for (auto system : systems) {
        system.second->setEnabled(true);
    }
}

void poison::DefaultEntityManager::update(float dt) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    
    for (auto system : systems) {
        if (system.second->isEnabled())
            system.second->update(dt);
    }
    
    for ( auto entity : entitiesToUpdate ) {
        entity->update(dt);
    }
}

void poison::DefaultEntityManager::registerForUpdate(Entity* e) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    entitiesToUpdate.emplace( e );
}

void poison::DefaultEntityManager::removeFromUpdate(Entity* e) {
    std::lock_guard<std::recursive_mutex> lock(mutex);
    entitiesToUpdate.erase( e );
}


