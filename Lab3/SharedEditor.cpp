#include "SharedEditor.h"

#include "NetworkServer.h"


SharedEditor::SharedEditor(NetworkServer networkServer) {
    networkServer.incrementSharedEditor();
    idSharedEditor = networkServer.getCounterSharedNetwork();
};

SharedEditor::~SharedEditor() = default;

int SharedEditor::getCodScharedEditor() {
    return this->idSharedEditor;
}

void SharedEditor::getMessage(Message) {
    //TODO: do stuffs
}