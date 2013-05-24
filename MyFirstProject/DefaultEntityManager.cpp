//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.




#include "defaultentitymanager.h"
#include "entitymanagerexception.h"

using namespace std;

DefaultEntityManager::DefaultEntityManager() {
    lastId = 1;
    maxId = numeric_limits<unsigned >::max();
}

DefaultEntityManager::~DefaultEntityManager() {
    cout << "default entity manager destructor" << endl;
    removeAllEntities();
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

void DefaultEntityManager::registerEntity(Entity *entity) {
    if (!entity->getId()) {
        entity->setId(generateNewUid());
        entities_.insert(std::pair<int, Entity*>(entity->getId(), entity));
    }
}

void DefaultEntityManager::removeEntity(Entity *entity) {

}

void DefaultEntityManager::addComponent(IComponent *component, Entity *entity) {

}

void DefaultEntityManager::removeComponent(string id, Entity *entity) {

}

IComponent *DefaultEntityManager::getComponent(string id, Entity *entity) {
    return NULL;
}

vector<IComponent *>  DefaultEntityManager::getComponentsForEntity(Entity *entity) {
    vector<IComponent*> v;
    return v;
}

vector<Entity *>  DefaultEntityManager::getEntitiesWithComponent(string id) {
    vector<Entity*> v;
    return v;
}

void DefaultEntityManager::registerSystem(string id, IComponentSystem *system) {

}

IComponentSystem *DefaultEntityManager::getSystem(string id) {
    return NULL;
}

void DefaultEntityManager::removeAllEntities() {
    for_each(entities_.begin(), entities_.end(), [](std::pair<int, Entity*> entity){
        delete entity.second;
    });

    entities_.clear();
}
