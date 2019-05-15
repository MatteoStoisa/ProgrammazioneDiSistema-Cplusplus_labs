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

};