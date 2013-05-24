#include <iostream>
#include "servicecontainer.h"
#include "iservice.h"

using namespace std;

void registerServices()
{
    ServiceContainer::sharedContainer().registerService("someId", new IService);
}

int main()
{
    registerServices();
    return 0;
}
