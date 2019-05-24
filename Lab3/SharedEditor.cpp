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

void SharedEditor::initCRDT() {
    this->_symbols.push_front(Symbol(' ',this->getIdScharedEditor(),-1,{0}));
    this->_symbols.push_back(Symbol(' ',this->getIdScharedEditor(),-1,{1}));
}

void SharedEditor::localInsert(int index,char value) {
    this->incrementCounterSharedEditor();
    //Symbol tempSymbol = Symbol(value,this->getIdScharedEditor(),this->getCounterSharedEditor(),this->calculateNewSRDT(index,this->_symbols));
    int i = 0;
    std::vector<int> newCRDT;
    for(auto it = this->_symbols.begin();it != this->_symbols.end();++it) {
        if (i == (index - 1)) {
            int j = 0;
            for (auto it2 = this->_symbols.begin()->getCRDTSymbol().begin();
                 it2 != this->_symbols.end()->getCRDTSymbol().end(); ++it2) {
                newCRDT[j] = it2[j];
                j++;
            }
            it->getCRDTSymbol()[j]++;
        }
        if (i == index) {
            this->_symbols.insert(it, Symbol(value, this->getIdScharedEditor(), this->getCounterSharedEditor(), newCRDT));
            break;
        }
    }

    void SharedEditor::localErase(int index) {
        int i = 0;
        for(auto it = this->_symbols.begin();it != this->_symbols.end();++it) {
            if (i == index) {
                this->_symbols.erase(it);
                break;
            }
        }
        this->_server.getMessageVector().insert(Message())
        //TODO: implement Message class and methods
    }




    //TODO: continue here
}
