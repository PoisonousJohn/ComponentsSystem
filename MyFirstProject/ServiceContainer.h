#include <map>
#include <string>
#include "ServiceInterface.h"
#ifndef SERVICECONTAINER_H
#define SERVICECONTAINER_H

using namespace std;

class ServiceContainer
{
private:
    static ServiceContainer container;
    map <string, ServiceInterface *> services_;

    ServiceContainer();
    ServiceContainer(const ServiceContainer&);
    ServiceContainer& operator=(const ServiceContainer&);
    ~ServiceContainer();

public:
    void registerService(string serviceId, ServiceInterface * service) {
        services_.insert(pair<string, ServiceInterface *>(serviceId, service));
    }

    ServiceInterface * getService(string serviceId) { return services_.at(serviceId); }

    static ServiceContainer& sharedContainer();

};

#endif // SERVICECONTAINER_H
