#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Base.h"
#include "File.h"

class Directory:Base {
private:
    Directory();

    std::vector<std::shared_ptr<Directory>> directoryPointers;
    std::vector<std::shared_ptr<File>> filePointers;
    std::weak_ptr<Directory> selfPointer;
    std::weak_ptr<Directory> fatherPointer;

public:
    static std::shared_ptr<Directory> getRoot();

};

#endif