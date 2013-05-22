#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "iservice.h"
#include <map>
#include <vector>
#include "icomponentsystem.h"
#include "icomponent.h"
#include "entity.h"

using namespace std;

class IEntityManager : public IService
{
private:
    unsigned int lastId_;

    map<string, Entity *> entities_;
    vector<IComponent *> components_;
    map<string, map<int, IComponent *> > componentsByClass_;
    map<unsigned int, vector<IComponent *> > componentsByEid_;
    map<string, IComponentSystem*> systemsByClass_;
public:
};

#endif // ENTITYMANAGER_H
