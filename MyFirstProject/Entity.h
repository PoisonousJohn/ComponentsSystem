
#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
protected:
    unsigned long int id;
public:
    Entity();
    virtual ~Entity();
    void setId(unsigned long int id);
    unsigned long int getId();
};

#endif // ENTITY_H
