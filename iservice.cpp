#include "iservice.h"
#include <iostream>

IService::IService()
{
}

IService::~IService()
{
    std::cout << "iservice destructor" << std::endl;
}
