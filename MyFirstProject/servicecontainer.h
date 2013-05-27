#include <map>
#include <string>
#include "IService.h"
#ifndef SERVICECONTAINER_H
#define SERVICECONTAINER_H

using namespace std;

class ServiceContainer
{
private:
    static ServiceContainer container;
    map <string, IService*> services_;

    ServiceContainer();
    ServiceContainer(const ServiceContainer&);
    ServiceContainer& operator=(const ServiceContainer&);
    ~ServiceContainer();

public:
    void registerService(string serviceId, IService* service) {
        services_.insert(pair<string, IService*>(serviceId, service));
    }

    IService* getService(string serviceId) { return services_.at(serviceId); }

    static ServiceContainer& sharedContainer();

};

#endif // SERVICECONTAINER_H
