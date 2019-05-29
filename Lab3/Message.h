#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#include "Symbol.h"

class Message {
private:
public:
    Message(Symbol,int,bool);
    ~Message();

    int sourceSharedEditor;
    Symbol symbol;
    bool isInsert;
};


#endif
