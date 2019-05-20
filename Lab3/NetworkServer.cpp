#include "NetworkServer.h"

#include <algorithm>
#include <iostream>

NetworkServer::NetworkServer() {
    this->counterSharedEditor = 0;
    this->idSharedEditor = 0;
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
    sharedEditor->setIdSharedEditor(this->idSharedEditor);
    this->idSharedEditor++;
    this->sharedEditorPointers.insert(this->sharedEditorPointers.end(), std::shared_ptr<SharedEditor>(sharedEditor));
    return this->counterSharedEditor;
}

void NetworkServer::disconnect(SharedEditor* sharedEditor) {
    auto it = std::find(this->sharedEditorPointers.begin(),this->sharedEditorPointers.end(),std::shared_ptr<SharedEditor>(sharedEditor));
    if(it != this->sharedEditorPointers.end()){
        if(sharedEditor->getIdScharedEditor() == it->get()->getIdScharedEditor()) {
            this->sharedEditorPointers.erase(it);
            std::cout << "Editor Disconnected correctly" << std::endl;
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
        this->messageStack.pop();
        //auto it = std::find(this->sharedEditorPointers.begin(),this->sharedEditorPointers.end(),std::shared_ptr<SharedEditor>(sharedEditor));
        for(std::vector<std::shared_ptr<SharedEditor>>::iterator it = this->sharedEditorPointers.begin();
            it != this->sharedEditorPointers.end();
            ++it) {
            if (temp.getSourceIdMessage() == it->get()->getIdScharedEditor()) {
                it->get()->getMessage(temp);
                std::cout << "Editor Disconnected correctly" << std::endl;
            }
        }
    }
}
