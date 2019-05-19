#ifndef BASE_H
#define BASE_H

class Base {
private:
public:
    friend class Directory;

    std::string name;

    std::string getName () const;
    void setName(std::string);
    virtual int mType () const;
    virtual void ls (int indent) const = 0;

    Base();
    ~Base();
};

#endif
