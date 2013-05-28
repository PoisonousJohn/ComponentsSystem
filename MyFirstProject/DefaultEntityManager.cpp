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

void DefaultEntityManager::removeComponent(componentId id, pEntity entity) {

}

void DefaultEntityManager::registerSystem(systemId id, ComponentSystemInterface *system) {

}

Component DefaultEntityManager::getComponent(componentId id, pEntity entity) {
    Component p;
    return p;
}

ComponentSystemInterface *DefaultEntityManager::getSystem(systemId id) {
    return NULL;
}
