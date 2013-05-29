#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <string>
#include "EntityManagerTypes.h"
#include "Entity.h"

class ComponentInterface
{
protected:
    entityId eid_;
    ComponentInterface() : eid_(0) {}

public:
    // multi_index tags
    struct componentIdTag{};
    struct entityIdTag{};



    entityId getEntityId() const { return eid_; }
    void setEntityId(const entityId eid) { eid_ = eid; }

    virtual std::string getId() const = 0;
    virtual void info() const = 0;
    virtual ~ComponentInterface();
};

#endif // ICOMPONENT_H
