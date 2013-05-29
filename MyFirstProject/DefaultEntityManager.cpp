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

    components_.clear();
    entitiesComponents_.clear();
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
//    auto entityComponents = components_.find(entity->getId());
    std::cout << "inserting component " << component->getId() << std::endl;
    componentsContainer_.insert_(component);
    component->setEntityId(entity->getId());
}

Component DefaultEntityManager::getComponent(componentId id, pEntity entity) {
    Component p;
    return p;
}

void DefaultEntityManager::removeEntity(pEntity entity) {

}

void DefaultEntityManager::removeComponent(componentId id, pEntity entity) {

}

void DefaultEntityManager::registerSystem(systemId id, ComponentSystemInterface *system) {

}

ComponentSystemInterface *DefaultEntityManager::getSystem(systemId id) {
    return NULL;
}


Objects<Component> DefaultEntityManager::getComponentsForEntity(pEntity entity) {
    return Objects<Component>();
}
Objects<Component> DefaultEntityManager::getComponentsWithId(componentId id) {
    return Objects<Component>();
}
