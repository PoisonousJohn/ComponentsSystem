#include "entitymanager.h"
#include <cstdlib>

EntityManager& EntityManager::instance()
{
    static EntityManager instance;
    pInstance_ = &instance;

    return *pInstance_;
}

void EntityManager::test() {

}

EntityManager::EntityManager()
{
}
