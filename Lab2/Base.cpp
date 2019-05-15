#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Base.h"

Base::Base() {
    std::cout<<"Base constructor\n";
}

std::string Base::getName() const {
    return this->name;
}

