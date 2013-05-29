//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/27/13.





#ifndef __TestComponent_H_
#define __TestComponent_H_

#include <iostream>
#include "ComponentInterface.h"


class TestComponent : public ComponentInterface {

public:
    virtual void info() const;

    virtual std::string getId() const;

    virtual ~TestComponent();
};


#endif //__TestComponent_H_
