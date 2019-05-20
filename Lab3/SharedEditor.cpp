#include "SharedEditor.h"

SharedEditor::SharedEditor() = default;
SharedEditor::~SharedEditor() = default;

int SharedEditor::getIdScharedEditor() {
    return this->idSharedEditor;
}

void SharedEditor::getMessage(Message) {
    //TODO: do stuffs
}

void SharedEditor::setIdSharedEditor(int id) {
    this->idSharedEditor = id;
}