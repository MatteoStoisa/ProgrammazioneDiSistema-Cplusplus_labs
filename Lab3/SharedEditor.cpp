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

int SharedEditor::getCounterSharedEditor() {
    return this->_counter;
}

void SharedEditor::incrementCounterSharedEditor() {
    this->_counter++;
}

void SharedEditor::setIdSharedEditor(int id) {
    this->_siteId = id;
}

void SharedEditor::receiveMessage(Message) {
    //TODO: do stuffs
}

void SharedEditor::localInsert(int index,char value) {
    this->incrementCounterSharedEditor();
    Symbol tempSymbol = new(Symbol(value,this->getIdScharedEditor(),this->getCounterSharedEditor(),this->calculateNewSRDT(index,this->_symbols)));
}

std::vector<int> SharedEditor::calculateNewSRDT(int index, std::vector<Symbol> symbols) {
    //TODO: order symbols, calculate index, calculate new SRDT

}


