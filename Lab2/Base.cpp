#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Base.h"

std::string Base::getName() const {
    return this->name;
}

void Base::setName(std::string nome) {
    this->name = nome;
    return;
}

int Base::mType() const {
    return 0;
}

Base::Base() = default;

Base::~Base() = default;
