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
    componentsByEid_.clear();
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

void DefaultEntityManager::removeEntity(pEntity entity) {

}

void DefaultEntityManager::addComponent(pIComponent component, pEntity entity) {
    auto componentIt = components_.find(component->getId());

    if (componentIt == components_.end()) {
        cout << "component " << component->getId() << " not found, creating" << endl;
        // making an empty pair
        componentsByEidMap map;
        auto pair = componentsByEidPair(component->getId(), map);
        componentIt = components_.insert(pair).first;
    }

    auto entityIt = componentIt->second.find(entity->getId());

    if (entityIt == componentIt->second.end()) {
        cout << "entity " << entity->getId() << " not found, creating" << endl;
        auto pair = componentsByEidMapPair(entity->getId(), componentsContainer());
//        map.insert();
        // making an empty pair
    }


}

void DefaultEntityManager::removeComponent(componentId id, pEntity entity) {

}

void DefaultEntityManager::registerSystem(systemId id, ComponentSystemInterface *system) {

}

pIComponent DefaultEntityManager::getComponent(componentId id, pEntity entity) {
    pIComponent p;
    return p;
}

Components DefaultEntityManager::getComponentsForEntity(pEntity entity) {
    Components p;
    return p;
}

Entities DefaultEntityManager::getEntitiesWithComponent(componentId id) {
    Entities p;
    return p;
}

ComponentSystemInterface *DefaultEntityManager::getSystem(systemId id) {
    return NULL;
}
