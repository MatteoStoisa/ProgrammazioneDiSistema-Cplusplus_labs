#ifndef LAB1_STRINGBUFFER_H
#define LAB1_STRINGBUFFER_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

class StringBuffer
{
private:
    int dimension;
    int	used;
    char* buffer;

public:
    StringBuffer();
    ~StringBuffer(void);
    StringBuffer(const char*);
    StringBuffer(const StringBuffer&);
    StringBuffer& operator= (const StringBuffer&);
    size_t size();
    size_t capacity();
    void clear();
    void insert(const char*, size_t);
    void insert (const StringBuffer&, size_t);
    char* getBuffer();
    void append (const char*);
    void append (const StringBuffer&);
    const char* c_str ();
    void set (const char*);
    void set (const StringBuffer&);

};

#endif //LAB1_STRINGBUFFER_H
