//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.




#include "DefaultEntityManager.h"
#include "EntityManagerException.h"
#include <limits>
#include <algorithm>

using namespace std;

DefaultEntityManager::DefaultEntityManager() {
    lastId = 1;
    maxId = numeric_limits<unsigned>::max();
}

DefaultEntityManager::~DefaultEntityManager() {
    cout << "default entity manager destructor" << endl;

    removeAllEntities();

    systems_.clear();

    cout << "entities count " << entities_.size() << endl;
}

unsigned long DefaultEntityManager::generateNewUid() {
    if (lastId < maxId) {
        return lastId++;
    } else {
        cerr << "failed to assign new uid to entity" << endl;
        throw EntityManagerException();
    }
}

void DefaultEntityManager::registerEntity(pEntity entity) {
    if (!entity->getId()) {
        entity->setId(generateNewUid());
        entities_.insert(std::pair<entityId, pEntity>(entity->getId(), entity));
    }
}

void DefaultEntityManager::removeAllEntities() {
    for_each(entities_.begin(), entities_.end(), [](std::pair<entityId, pEntity > entity){
        delete entity.second;
    });

    entities_.clear();
}

void DefaultEntityManager::addComponent(Component component, pEntity entity) {
    std::cout << "inserting component " << component->getId() << std::endl;

    component->setEntityId(entity->getId());
    componentsContainer_.insert(component);

    std::cout << "components count " << componentsContainer_.size() << std::endl;
}

Component DefaultEntityManager::getComponent(componentId id, pEntity entity) {
    auto componentIt = componentsContainer_.get<ComponentInterface::byComponentAndEntityIdTag>().find(boost::tuples::make_tuple(id, entity->getId()));
    auto endIt = componentsContainer_.get<ComponentInterface::byComponentAndEntityIdTag>().end();

    if (componentIt != endIt) {
        return *componentIt;
    }

    std::cerr << "Component not found" << std::endl;
    throw EntityManagerException();
}

void DefaultEntityManager::removeEntity(pEntity entity) {
    entities_.erase(entity->getId());
    ComponentsIndex::index<ComponentInterface::byEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<ComponentInterface::byEntityIdTag>().equal_range(entity->getId());
    componentsContainer_.get<ComponentInterface::byEntityIdTag>().erase(first, last);
}

void DefaultEntityManager::removeComponent(componentId id, pEntity entity) {
    ComponentsIndex::index<ComponentInterface::byComponentAndEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<ComponentInterface::byComponentAndEntityIdTag>().equal_range(boost::tuples::make_tuple(id, entity->getId()));
    componentsContainer_.get<ComponentInterface::byComponentAndEntityIdTag>().erase(first, last);
}

void DefaultEntityManager::registerSystem(systemId id, ComponentSystem system) {
    systems_.insert(std::make_pair(id, system));
}

ComponentSystem DefaultEntityManager::getSystem(systemId id) {
    return systems_.at(id);
}

Components DefaultEntityManager::getComponentsForEntity(pEntity entity) {
    ComponentsIndex::index<ComponentInterface::byEntityIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<ComponentInterface::byEntityIdTag>().equal_range(entity->getId());
    return Components(first, last);
}
Components DefaultEntityManager::getComponentsWithId(componentId id) {
    ComponentsIndex::index<ComponentInterface::byComponentIdTag>::type::iterator first, last;
    boost::tuples::tie(first, last) = componentsContainer_.get<ComponentInterface::byComponentIdTag>().equal_range(id);
    return Components(first, last);
}
