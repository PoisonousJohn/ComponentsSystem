//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/27/13.




#include "TestComponent.h"
#include <iostream>
#include <string>

void TestComponent::info() const {
    std::cout << "test component for entity " << eid_ << std::endl;
}


std::string TestComponent::getId() const {
    return std::string("testComponentId");
}

TestComponent::~TestComponent() {
    std::cout << "test component for entity " << eid_  << " destructor" << std::endl;
}



