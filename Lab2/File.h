#include "Base.h"

class File:Base {
private:
    size_t size;
public:
    uintmax_t getSize () const;

    void ls (int indent=0) const override;
};