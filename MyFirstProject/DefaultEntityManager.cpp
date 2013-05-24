//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/24/13.




#include "defaultentitymanager.h"
#import "entitymanagerexception.h"
#include <vector>

using namespace std;

DefaultEntityManager::DefaultEntityManager() {
    lastId = 1;
    maxId = numeric_limits<unsigned >::max();
}

DefaultEntityManager::~DefaultEntityManager() {

}

unsigned long DefaultEntityManager::generateNewUid() {
    if (lastId < maxId) {
        return lastId++;
    } else {
        cerr << "failed to assign new uid to entity";
        throw EntityManagerException();
    }
}

void DefaultEntityManager::registerEntity(Entity *entity) {
    entity->p_nId = 2;
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

//vector<IComponent *>  DefaultEntityManager::getComponentsForEntity(Entity *entity) {
//    return 0;
//}

//vector<Entity *>  DefaultEntityManager::getEntitiesWithComponent(string id) {
//    return NULL;
//}

void DefaultEntityManager::registerSystem(string id, IComponentSystem *system) {

}

IComponentSystem *DefaultEntityManager::getSystem(string id) {
    return NULL;
}

void DefaultEntityManager::removeAllEntities() {

}
