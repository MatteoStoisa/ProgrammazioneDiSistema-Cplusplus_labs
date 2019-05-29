#include <iostream>

#include "SharedEditor.h"

SharedEditor::SharedEditor(NetworkServer& ns) : _server(const_cast<NetworkServer&> (ns)){
    this->setIdSharedEditor(this->_server.connect(this));
    this->_counter = 0;
    this->initCRDT();
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

void SharedEditor::initCRDT() {
    this->_symbols.push_front(Symbol(' ',this->getIdScharedEditor(),-1,{0}));
    this->_symbols.push_back(Symbol(' ',this->getIdScharedEditor(),-1,{1}));
}

void SharedEditor::localInsert(int index,char value) {
  this->incrementCounterSharedEditor();
  std::vector<int> newCRDT;
  Symbol newSymbol = Symbol(value, this->getIdScharedEditor(), this->getCounterSharedEditor(), newCRDT);
  int i = 0; //counter on iterator it

  for (auto it = this->_symbols.begin(); it != this->_symbols.end(); ++it) { //iterator on symbol list
    if (i == index) { //when arrived before index symbol
      int j = 0;
      for (auto it2 = it->positionCRDT.begin();
           it2 != it->positionCRDT.end(); ++it2) { //iterator: copy of previous CRDT
        newSymbol.positionCRDT.push_back(*it2);
        j++;
      }
      j--;
      auto itPre = it; //pre index
      it++; //post index
      //TODO: switch case on (it->positionCRDT.size() - itPre->positionCRDT.size()) >=< 0

      int diff = (it->positionCRDT.size() - itPre->positionCRDT.size());
      // >0 add as many zeros
      // ==0 check: (postCRDT[j] - preCRTD[j])>1 add 1, or push_back(1)
      // <0 preCRDT[j] add1

      if(diff > 0 ) {
        for(int k = 0; k < diff; k++) {
          newCRDT.push_back(0);
        }
        newCRDT.push_back(1);
      }
      else {
        if() //TODO: copntinue here
      }




      if(it->positionCRDT.size() == itPre->positionCRDT.size()) {
        if ((it->positionCRDT[j] - itPre->positionCRDT[j]) > 1) {
          newSymbol.positionCRDT[j]++;
        } else {
          newSymbol.positionCRDT.push_back(1);
        }
      }
      else {
        if(it->positionCRDT.size() > itPre->positionCRDT.size())

        newSymbol.positionCRDT.push_back(1);
      }
      this->_symbols.insert(it, newSymbol);
    }
    i++;
  }
  Message tempM = Message(newSymbol, this->getIdScharedEditor(), true);
  this->_server.messageVector.push_back(tempM);
}

void SharedEditor::localErase(int index) {
    int i = 0;
    for(auto it = this->_symbols.begin();it != this->_symbols.end();++it) {
        if (i == index) {
            this->_symbols.erase(it);
            break;
        }
    }
    this->_server.messageVector.push_back(Message(Symbol(' ',-1,-1,std::vector<int> {}),this->getIdScharedEditor(),false));
}

std::string SharedEditor::to_string() {
    std::string output;
    for(auto it = this->_symbols.begin();it != this->_symbols.end();++it) {
        output.append(&it->symbol);
    }
    std::cout<<output;
}

void SharedEditor::process(const Message& m) {
    if(m.isInsert) {
        for(auto it = this->_symbols.begin(); it != this->_symbols.end(); ++it) {
            try {
                if(it->positionCRDT == m.symbol.positionCRDT) {
                    throw 0 ;
                }
                if(it->positionCRDT > m.symbol.positionCRDT) {
                    --it;
                    this->_symbols.insert(it,m.symbol);
                }
            }
            catch(int a) {
                std::cout<<"collision";
                exit(-1);
            }
        }
    }
    else {
        for(auto it = this->_symbols.begin(); it != this->_symbols.end(); ++it) {
            if(it->positionCRDT == m.symbol.positionCRDT)
                this->_symbols.erase(it);
        }
    }
}
