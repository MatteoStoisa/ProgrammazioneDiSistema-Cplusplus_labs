#include "NetworkServer.h"

#include <algorithm>
#include <iostream>

NetworkServer::NetworkServer() {
    this->counterSharedEditor = 0;
}

NetworkServer::~NetworkServer() = default;

int NetworkServer::getCounterSharedNetwork() {
    return this->counterSharedEditor;
}

void NetworkServer::incrementSharedEditor() {
    this->counterSharedEditor++;
}


int NetworkServer::connect(SharedEditor* sharedEditor) {
    this->counterSharedEditor++;
    this->sharedEditorPointers.insert({this->counterSharedEditor,std::shared_ptr<SharedEditor>(sharedEditor)});
    return this->counterSharedEditor;
}

void NetworkServer::disconnect(SharedEditor* sharedEditor) {
    for(auto it = this->sharedEditorPointers.begin();it == this->sharedEditorPointers.end();++it) {
        if(this->sharedEditorPointers.find(it)->second == sharedEditor) {
            this->sharedEditorPointers.erase(it);
            std::cout<<"Editor Disconnected correctly"<<std::endl;
        }
    }
}

void NetworkServer::send(const Message& m) {
    this->messageStack.push(m);
}

void NetworkServer::dispatchMessages() {
    Message temp;
    while(this->messageStack.empty()) {
        temp = this->messageStack.top();
        for(auto it = this->sharedEditorPointers.begin();it == this->sharedEditorPointers.end();++it) {
            if(temp.getSourceMessage() != this->sharedEditorPointers.at(it)) {
                this->sharedEditorPointers.find(it)->getMessage(temp);
                this->messageStack.pop();
            }

        }
    }
}
