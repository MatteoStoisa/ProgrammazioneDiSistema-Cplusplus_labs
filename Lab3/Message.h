#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#include "Symbol.h"

class Message {
private:
    int sourceSharedEditor;
public:
    Message(Symbol,bool);
    ~Message();

    bool isInsert;
    Symbol symbolOrNULL;

    int getSourceIdMessage();
};


#endif
