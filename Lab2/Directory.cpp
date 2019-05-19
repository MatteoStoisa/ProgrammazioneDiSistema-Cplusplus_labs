#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>


#include "Directory.h"

std::shared_ptr<Directory> Directory::root;

Directory::Directory() = default;

Directory::~Directory() = default;

//getter

std::shared_ptr<Directory> Directory::getSelfPointer() const {
    return this->selfPointer.lock();
}

std::shared_ptr<Directory> Directory::getFatherPointer() const {
    return this->fatherPointer.lock();
}

//setter

void Directory::setSelfPointer(std::weak_ptr<Directory> weakPtr) {
    this->selfPointer = weakPtr;
}

void Directory::setFatherPointer(std::weak_ptr<Directory> weakPtr) {
    this->fatherPointer = weakPtr;
}

//miscellaneous

Directory &Directory::operator=(Directory *) {
    return *this;
}

int Directory::mType() const {
    return 1;
}

Directory::Directory(std::string name) {
    this->name = std::move(name);
}

//

std::shared_ptr<Directory> Directory::getRoot() {
    if(!root) {
        Directory::root = std::shared_ptr<Directory>(new Directory("/"));
        Directory::root.get()->setSelfPointer(Directory::root);
        Directory::root.get()->setFatherPointer(Directory::root);
    }
    return root;
}

std::shared_ptr<Directory> Directory::addDirectory (std::string nome) {
    try {
        if(this->innerDirectoryPointers.find(nome) != this->innerDirectoryPointers.end())
            throw(nome);
        std::shared_ptr<Directory> newDirectoryPtr = std::shared_ptr<Directory>(new Directory(nome));
        newDirectoryPtr->setSelfPointer(newDirectoryPtr);
        newDirectoryPtr->setFatherPointer(this->getSelfPointer());
        this->innerDirectoryPointers.insert({nome,newDirectoryPtr});
        return newDirectoryPtr;
    }
    catch(std::string nome) {
        std::cout<<nome<<" already exists\n";
    }
}

std::shared_ptr<File> Directory::addFile (std::string nome, uintmax_t size) {
    try {
        if(this->innerFilePointers.find(nome) != this->innerFilePointers.end())
            throw(nome);
        std::shared_ptr<File> newFilePtr = std::shared_ptr<File>(new File(nome,size));
        this->innerFilePointers.insert({nome,newFilePtr});
        return newFilePtr;
    }
    catch(std::string nome) {
        std::cout<<nome<<" already exists\n";
    }
}

std::shared_ptr<Base> Directory::get (std::string nome) {
    if (nome == "..") {
        return this->getFatherPointer();
    }

    if (nome == ".") {
        return this->getSelfPointer();
    }
    try {
        std::shared_ptr<Base> search = this->innerFilePointers.find(nome)->second;
        if(this->innerFilePointers.end()->second == search)
            std::shared_ptr<Base> search = this->innerDirectoryPointers.find(nome)->second;
        if(this->innerDirectoryPointers.end()->second == search)
            throw nome;
        return search;
    }
    catch(std::string nome) {
        std::cout<<"nome non presente\n";
        exit(-1);
    }
}

std::shared_ptr<Directory> Directory::getDir (std::string nome) {
    if (nome == "..") {
        return this->getFatherPointer();
    }
    if (nome == ".") {
        return this->getSelfPointer();
    }
    try {
        std::shared_ptr<Base> search = this->innerDirectoryPointers.find(nome)->second;
        if(this->innerDirectoryPointers.end()->second == search)
            throw nome;
        return std::dynamic_pointer_cast<Directory>(search);
    }
    catch(std::string nome) {
        std::cout<<"directory "<<nome<<" doesnt exist\n";
    }
}

std::shared_ptr<File> Directory::getFile (std::string nome) {
    try {
        std::shared_ptr<Base> search = this->innerFilePointers.find(nome)->second;
        if(this->innerFilePointers.end()->second == search)
            throw nome;
        return std::dynamic_pointer_cast<File>(search);
    }
    catch(std::string nome) {
        std::cout<<"file "<<nome<<" doesnt exist\n";
    }
}

void Directory::remove (std::string nome) {
    try {
        if(nome == "." || nome == "..")
            throw("...");
        if((this->innerFilePointers.find(nome) == innerFilePointers.end()) && (this->innerDirectoryPointers.find(nome) == innerDirectoryPointers.end()))
            throw(nome);
        if(this->innerFilePointers.find(nome)->second->mType() == 2) //TODO: maybe to fix
            this->innerFilePointers.erase(nome);
        else {
            this->innerDirectoryPointers.find(nome)->second->recoursiveDelete();
            this->innerDirectoryPointers.erase(nome);
        }
    }
    catch(std::string nome) {
        if(nome == "...") {
            std::cout<<"cant remove father or self\n";
        }
        std::cout<<"file or directory "<<nome<<" doesnt exist\n";
    }
}

void Directory::recoursiveDelete() {
    for (std::map<std::string,std::shared_ptr<Directory>>::const_iterator it = this->innerDirectoryPointers.begin(); it != this->innerDirectoryPointers.end(); ++it) {
        std::string temp = it->first;
        this->innerFilePointers.clear();
        this->innerDirectoryPointers.find(temp)->second->recoursiveDelete();
        this->innerDirectoryPointers.erase(temp);

    }
}

void Directory::ls (int indent) const {
    if(indent == 0) {
        std::cout << "--- ls ---\n";
        std::cout << "[+] " << this->getName() << "\n";
        indent+=6;
    }
    for (std::map<std::string,std::shared_ptr<Directory>>::const_iterator it = this->innerDirectoryPointers.begin(); it != this->innerDirectoryPointers.end(); ++it)
    {
        for(int i=0;i<indent;i++)
            std::cout<<" ";
        if(it->second->mType() == 1) {
            std::cout<< "[+] " << it->second->getName()<<"\n";
            it->second->ls(indent + 6);
        }
        else {
            std::cout<<it->second->getName()<<"\n";
        }
    }
}