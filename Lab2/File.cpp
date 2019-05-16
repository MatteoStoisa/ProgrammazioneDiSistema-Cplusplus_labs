#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "File.h"

uintmax_t File::getSize () const {
    return this->size;
}

File::File(std::string nome,size_t dim) {
    this->name = nome;
    this->size = dim;
}

int File::mType() const {
    return 0;
}

File::~File() = default;

/*void File::ls (int indent=0) const {
    std::cout<<"File name "<<this->getName()<<" size "<<this->size;
}*/
