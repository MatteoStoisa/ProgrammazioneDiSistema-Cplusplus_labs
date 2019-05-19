#ifndef LAB3_NETWORKSERVER_H
#define LAB3_NETWORKSERVER_H

#include <bits/shared_ptr.h>
#include <vector>
#include <map>
#include <stack>

#include "SharedEditor.h"
#include "message.h"

std::map<int, std::shared_ptr<SharedEditor>> sharedEditorPointers; //why not working??
std::stack<Message> messageStack;

int codSharedEditor;

class NetworkServer {
private:

public:
    int connect(SharedEditor*);
};


#endif
