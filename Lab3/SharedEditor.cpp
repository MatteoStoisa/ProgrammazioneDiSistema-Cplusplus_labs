#include "SharedEditor.h"
#include "NetworkServer.h"

SharedEditor::SharedEditor() {
    codSharedEditor = ++counterSharedEditor;
};

SharedEditor::~SharedEditor() = default;

int SharedEditor::getCodScharedEditor() {
    return this->codSharedEditor;
}