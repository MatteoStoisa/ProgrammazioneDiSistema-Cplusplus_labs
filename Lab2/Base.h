#ifndef BASE_H
#define BASE_H

class Base {
private:
    std::string name;
public:
    Base();

    std::string getName () const;
    //virtual int mType () const = 0;
    //virtual void ls (int indent=0) const = 0;
};

#endif
