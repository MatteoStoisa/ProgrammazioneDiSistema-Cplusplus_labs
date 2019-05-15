#ifndef FILE_H
#define FILE_H

#include "Base.h"

class File:Base {
private:
    size_t size;
public:
    File();
    uintmax_t getSize () const;
    //void ls (int) const override;
};

#endif