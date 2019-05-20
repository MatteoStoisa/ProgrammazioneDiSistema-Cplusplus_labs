#include "NetworkServer.h"

NetworkServer::NetworkServer() = default;

NetworkServer::~NetworkServer() = default;

int connect(SharedEditor* sharedEditor) {
    std::vector<std::shared_ptr<SharedEditor>.iterator it; //TODO: insert
    auto it = sharedEditorPointers.insert(it,sharedEditorPointers.begin(),&sharedEditor); //??
    return sharedEditor->getCodScharedEditor();
}