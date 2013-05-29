#ifndef ENTITY_H
#define ENTITY_H

#include "EntityManagerTypes.h"

class Entity
{
protected:
    entityId id;
public:
    Entity();
    virtual ~Entity();
    void setId(entityId id);
    entityId getId() const;
};

#endif // ENTITY_H
