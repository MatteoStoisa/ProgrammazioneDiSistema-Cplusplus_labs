#include "Message.h"

Message::Message(Symbol symbolInserted,bool insert) : symbol(const_cast<Symbol&> (symbolInserted)) {
    isInsert = insert;
    symbol = symbolInserted;
}

Message::~Message() = default;

int Message::getSourceIdMessage() {
    return this->sourceSharedEditor;
}
