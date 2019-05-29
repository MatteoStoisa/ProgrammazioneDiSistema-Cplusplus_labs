#include "Message.h"

Message::Message(Symbol symbolInserted, int id, bool insert) : symbol(const_cast<Symbol&> (symbolInserted)) {
    isInsert = insert;
    symbol = symbolInserted;
    sourceSharedEditor = id;
}

Message::~Message() = default;
