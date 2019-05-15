#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Directory.h"

extern bool existRoot;

Directory::Directory() {
    std::cout<<"Directory constructor\n";
}

std::shared_ptr<Directory> Directory::getRoot() {
    if(existRoot == true)
        return NULL;
    else {
        existRoot = true;
        std::shared_ptr<Directory> newRoot(new Directory());
        return newRoot;
    }
}
