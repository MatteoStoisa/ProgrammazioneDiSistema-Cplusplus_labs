#include "Message.h"

Message::Message(bool isInsert) {
    isInsertMessage = isInsert;
}
Message::~Message() = default;

int Message::getSourceIdMessage() {
    return this->sourceSharedEditor;
}
