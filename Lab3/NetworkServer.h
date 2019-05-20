#ifndef LAB3_NETWORKSERVER_H
#define LAB3_NETWORKSERVER_H

#include <vector>
#include <stack>
#include <map>
#include <memory>

#pragma once

#include "SharedEditor.h"
#include "Message.h"

class NetworkServer {
private:
    std::vector<std::shared_ptr<SharedEditor>> sharedEditorPointers;
    std::stack<Message> messageStack;
    int counterSharedEditor;
    int idSharedEditor;
public:
    NetworkServer();
    ~NetworkServer();

    int getCounterSharedNetwork();
    void incrementSharedEditor();

    int connect(SharedEditor*);
    void disconnect(SharedEditor* sharedEditor);
    void send(const Message& m);
    void dispatchMessages();
};


#endif
