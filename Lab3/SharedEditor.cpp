#include "SharedEditor.h"

SharedEditor::SharedEditor(NetworkServer& ns) : _server(const_cast<NetworkServer&> (ns)){
    this->_server = ns; //TODO: does it works?
    this->setIdSharedEditor(this->_server.connect(this));
    this->_counter = 0;
}

SharedEditor::~SharedEditor() = default;

int SharedEditor::getIdScharedEditor() {
    return this->_siteId;
}

void SharedEditor::setIdSharedEditor(int id) {
    this->_siteId = id;
}

void SharedEditor::receiveMessage(Message) {
    //TODO: do stuffs
}

void localInsert(int index,char value) {
    //TODO: continue here
}
