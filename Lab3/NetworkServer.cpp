#include "NetworkServer.h"

#include <algorithm>
#include <iostream>

NetworkServer::NetworkServer() {
    this->idSharedEditorGenerator = 0;
}

NetworkServer::~NetworkServer() = default;

int NetworkServer::generateIdSharedNetwork() {
    return this->idSharedEditorGenerator;
}

void NetworkServer::incrementSharedEditor() {
    this->idSharedEditorGenerator++;
}


int NetworkServer::connect(SharedEditor* sharedEditor) {
    sharedEditor->setIdSharedEditor(this->idSharedEditorGenerator);
    this->sharedEditorPointers.insert({this->idSharedEditorGenerator, std::shared_ptr<SharedEditor>(sharedEditor)});
    this->incrementSharedEditor();
    return sharedEditor->getIdScharedEditor();
}

void NetworkServer::disconnect(SharedEditor* sharedEditor) {
    this->sharedEditorPointers.erase(sharedEditor->getIdScharedEditor());
}

void NetworkServer::send(const Message& m) {
    this->messageVector.push_back(m);
}

void NetworkServer::dispatchMessages() {
    for(auto itM = this->messageVector.begin(); itM != this->messageVector.end(); ++itM) {
        for(auto itS = this->sharedEditorPointers.begin(); itS != this->sharedEditorPointers.end(); ++itS) {
            if(itM->sourceSharedEditor != itS->first) {
                itS->second->process(*itM); //TODO: crash here
                this->messageVector.erase(itM);
            }
        }
    }
}
