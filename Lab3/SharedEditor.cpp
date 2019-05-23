#include "SharedEditor.h"

SharedEditor::SharedEditor(NetworkServer& ns) : _server(const_cast<NetworkServer&> (ns)){
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

void SharedEditor::initSRDT() {
    this->_symbols.push_back(Symbol(' ',this->getIdScharedEditor(),-1,{0}));
    this->_symbols.push_back(Symbol(' ',this->getIdScharedEditor(),-1,{1}));
}

void SharedEditor::localInsert(int index,char value) {
    this->incrementCounterSharedEditor();
    Symbol tempSymbol = Symbol(value,this->getIdScharedEditor(),this->getCounterSharedEditor(),this->calculateNewSRDT(index,this->_symbols));
    //TODO: continue here
}

std::vector<int> SharedEditor::calculateNewSRDT(int index, std::vector<Symbol> symbols) {
    //TODO: order symbols, calculate index, calculate new SRDT
    for(int countSymbol = 0;countSymbol < this->_symbols.size(); countSymbol++) {

    }

    for(int countIndex = 0;countIndex < index ;countIndex++) {

    }

}


