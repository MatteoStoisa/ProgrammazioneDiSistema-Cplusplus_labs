#include "Symbol.h"

Symbol::Symbol(char character,int sourceId,int sourceCounter,std::vector<int> position) {
    this->symbol = character;
    this->symbolSourceId = sourceId;
    this->symbolSourceCounter = sourceCounter;
    this->positionCRDT = position;
}

Symbol::~Symbol() = default;
