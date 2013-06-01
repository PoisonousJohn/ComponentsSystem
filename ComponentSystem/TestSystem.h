#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H

#include <iostream>
#include "ComponentSystemInterface.h"

class TestSystem : public ComponentSystemInterface
{
public:
    TestSystem();
    virtual ~TestSystem();
    virtual std::string info() const;
};

#endif // TESTSYSTEM_H
