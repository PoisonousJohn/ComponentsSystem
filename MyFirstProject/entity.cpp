#include <iostream>
#include "entity.h"

Entity::Entity()
{
    id = 0;
}

Entity::~Entity() {
    std::cout << "entity " << id << " destructor" << std::endl;
}

void Entity::setId(unsigned long id) {
    this->id = id;
}

unsigned long Entity::getId() {
    return id;
}







