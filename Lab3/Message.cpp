#include "Message.h"

Message::Message(Symbol symbolInserted,bool insert) : symbolOrNULL(const_cast<Symbol&> (symbolInserted)) {
    isInsert = insert;
}

Message::~Message() = default;

int Message::getSourceIdMessage() {
    return this->sourceSharedEditor;
}
