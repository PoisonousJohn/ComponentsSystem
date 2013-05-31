#include "ServiceInterface.h"
#include <iostream>

ServiceInterface::ServiceInterface()
{
}

ServiceInterface::~ServiceInterface()
{
    std::cout << "iservice destructor" << std::endl;
}
