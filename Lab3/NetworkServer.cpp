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
    this->sharedEditorPointers.push_back(std::shared_ptr<SharedEditor>(sharedEditor));
    return this->counterSharedEditor;
}

void NetworkServer::disconnect(SharedEditor* sharedEditor) {
    auto it = std::find(this->sharedEditorPointers.begin(),this->sharedEditorPointers.end(),std::shared_ptr<SharedEditor>(sharedEditor));
    if(it != this->sharedEditorPointers.end()){
        this->sharedEditorPointers.erase(it);
        std::cout<<"Editor Disconnected correctly"<<std::endl;
    }
}

void NetworkServer::send(const Message& m) {
    this->messageStack.push(m);
}

void NetworkServer::dispatchMessages() {
    Message temp;
    while(this->messageStack.empty()) {
        temp = this->messageStack.top();
        this->messageStack.pop();
        for(auto it = this->sharedEditorPointers.begin();it == this->sharedEditorPointers.end();++it) {
            if(temp.getSourceMessage() != this->sharedEditorPointers[it].) {
                this->sharedEditorPointers.find(it)->getMessage(temp);
            }

        }
    }
}
