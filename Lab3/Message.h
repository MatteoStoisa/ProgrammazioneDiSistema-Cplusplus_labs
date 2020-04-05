#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#include "Symbol.h"

class Message {
private:
    int sourceSharedEditor;
public:
    Message(Symbol,bool);
    ~Message();

    Symbol symbol;
    bool isInsert;
    std::vector<int> symbolCRDT;

    int getSourceIdMessage();
};


#endif
