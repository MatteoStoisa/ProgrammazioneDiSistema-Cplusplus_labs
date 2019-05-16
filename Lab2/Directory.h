#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <map>
#include "Base.h"
#include "File.h"

class Directory:Base {
private:
    std::map<std::string,std::shared_ptr<Base>> innerPointers;
    std::weak_ptr<Directory> selfPointer; //come si fa??
    std::weak_ptr<Directory> fatherPointer;

public:
    Directory(std::string);

    //getter
    std::shared_ptr<Directory> getSelfPointer();
    std::shared_ptr<Directory> getFatherPointer();
    //setter
    void setSelfPointer(std::weak_ptr<Directory>);
    void setFatherPointer(std::weak_ptr<Directory>);
    //miscellaneous
    Directory &operator=(Directory *d);
    //int mType() const override;

    static std::shared_ptr<Directory> root;
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory (std::string);
    std::shared_ptr<File> addFile (std::string, uintmax_t);
    std::shared_ptr<Base> get (std::string);

protected:
    Directory();
    //~Directory();
};

#endif