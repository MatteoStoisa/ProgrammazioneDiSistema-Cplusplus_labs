#include "SharedEditor.h"

SharedEditor::SharedEditor() = default;
SharedEditor::~SharedEditor() = default;

int SharedEditor::getIdScharedEditor() {
    return this->idSharedEditor;
}

void SharedEditor::setIdSharedEditor(int id) {
    this->idSharedEditor = id;
}

void SharedEditor::receiveMessage(Message) {
    //TODO: do stuffs
}