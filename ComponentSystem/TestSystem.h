#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H

#include <iostream>
#include "ComponentSystemInterface.h"

class TestSystem : public ComponentSystemInterface
{
public:
    TestSystem();
    virtual ~TestSystem();

};

//std::ostream & operator << (std::ostream &ostream, const TestSystem &)
//{
//    ostream << "test system";
//    return ostream;
//}

#endif // TESTSYSTEM_H
