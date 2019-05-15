
// PDS Lab2
// File System di directory e file

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Base.h"
#include "Directory.h"
#include "File.h"

bool existRoot;

int main() {
    existRoot = false;
    std::cout << "--- Lab2 ---" << std::endl;

    std::shared_ptr<Directory> root = Directory::getRoot();
    std::cout<<"Root creata\n";

    return 0;
}