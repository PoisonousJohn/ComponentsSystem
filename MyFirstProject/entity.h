#ifndef ENTITY_H
#define ENTITY_H

#include "IEntityManager.h"

class Entity
{
protected:
    unsigned int p_nId;
public:
    Entity();

    friend class IEntityManager;
};

#endif // ENTITY_H
