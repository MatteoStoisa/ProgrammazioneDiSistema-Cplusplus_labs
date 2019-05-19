#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <map>
#include "Base.h"
#include "File.h"

class Directory: public Base {
private:
    std::map<std::string,std::shared_ptr<Directory>> innerDirectoryPointers;
    std::map<std::string,std::shared_ptr<File>> innerFilePointers;
    std::weak_ptr<Directory> selfPointer; //come si fa??
    std::weak_ptr<Directory> fatherPointer;

public:

    //getter
    std::shared_ptr<Directory> getSelfPointer() const;
    std::shared_ptr<Directory> getFatherPointer() const;
    //setter
    void setSelfPointer(std::weak_ptr<Directory>);
    void setFatherPointer(std::weak_ptr<Directory>);
    //miscellaneous
    Directory &operator=(Directory *d);
    int mType() const override;
    ~Directory();

    static std::shared_ptr<Directory> root;
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory (std::string);
    std::shared_ptr<File> addFile (std::string, uintmax_t);
    std::shared_ptr<Base> get (std::string);
    std::shared_ptr<Directory> getDir (std::string);
    std::shared_ptr<File> getFile (std::string);
    void remove (std::string);
    void ls (int indent = 0) const override;

    void recoursiveDelete();

protected:
    Directory();
    explicit Directory(std::string);

};

#endif