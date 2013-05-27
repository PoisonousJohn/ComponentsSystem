//
// Created by JohnPoison <truefiresnake@gmail.com> on 5/27/13.




#include "TestComponent.h"
#include <iostream>
#include <string>

void TestComponent::info() {
    std::cout << "test component" << std::endl;
}


std::string TestComponent::getId() {
    return std::string("testComponentId");
}

TestComponent::~TestComponent() {
    std::cout << "test component destructor" << std::endl;
}



