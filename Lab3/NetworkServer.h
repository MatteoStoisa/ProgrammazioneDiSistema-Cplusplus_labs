#ifndef LAB3_NETWORKSERVER_H
#define LAB3_NETWORKSERVER_H

#include <bits/shared_ptr.h>
#include <vector>
#include <stack>

#include "SharedEditor.h"
#include "Message.h"

std::vector<std::shared_ptr<SharedEditor>> sharedEditorPointers;
std::stack<Message> messageStack;

int counterSharedEditor = 0;

class NetworkServer {
private:

public:
    NetworkServer();
    ~NetworkServer();

    int connect(SharedEditor*);
};


#endif
