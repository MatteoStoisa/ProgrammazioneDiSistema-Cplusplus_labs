
// PDS Lab2
// File System di directory e file

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Base.h"
#include "Directory.h"
#include "File.h"

std::shared_ptr<Directory> root;

int main() {
    std::cout << "--- Lab2 ---" << std::endl;

    root = Directory::getRoot();
    root->Directory::addDirectory("directory1");
    root->Directory::addFile("file1",100);
    root->Directory::addFile("file2",200);
    std::cout<<root->Directory::get("file1").get()->getName();

    return 0;
}