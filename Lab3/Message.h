#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#pragma once

class Message {
private:
    int sourceSharedEditor;
public:
    Message(bool);
    ~Message();
    bool isInsertMessage;

    int getSourceIdMessage();
};


#endif
