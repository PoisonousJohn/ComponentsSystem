#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>
#include "EntityManagerTypes.h"
#include "Entity.h"

class ComponentInterface
{
protected:
    entityId eid_;

public:
    ComponentInterface() : eid_(0) {}
    // multi_index tags
    struct byComponentIdTag {};
    struct byEntityIdTag {};
    struct byComponentAndEntityIdTag{};



    entityId getEntityId() const { return eid_; }
    void setEntityId(const entityId eid) { eid_ = eid; }

    virtual std::string getId() const = 0;
    virtual void info() const = 0;
    virtual ~ComponentInterface();
};

#endif // ICOMPONENT_H
