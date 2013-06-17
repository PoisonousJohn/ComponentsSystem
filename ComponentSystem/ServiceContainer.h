#ifndef SERVICECONTAINER_H
#define SERVICECONTAINER_H

#include <map>
#include <string>
#include <memory>
#include "ServiceInterface.h"

class ServiceContainer
{
private:
    static ServiceContainer container;
    std::map <std::string, std::shared_ptr<ServiceInterface> > services_;

    ServiceContainer();
    ~ServiceContainer();
    
    // forbid copy
    ServiceContainer(const ServiceContainer&);
    ServiceContainer& operator=(const ServiceContainer&);
    
public:
    void registerService(std::string serviceId, ServiceInterface * service) {
        services_.insert(std::make_pair(serviceId, std::shared_ptr<ServiceInterface>(service)));
    }

    std::shared_ptr<ServiceInterface> getService(std::string serviceId) { return services_.at(serviceId); }

    static ServiceContainer& sharedContainer();

};

#endif // SERVICECONTAINER_H
