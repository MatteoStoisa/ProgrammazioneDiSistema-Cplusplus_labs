#ifndef FILE_H
#define FILE_H

#include "Base.h"

class File: public Base {
private:
    size_t size;
public:
    uintmax_t getSize () const;

    int mType() const override;
    //void ls (int) const override;

    File(std::string,size_t);
    ~File();

};

#endif