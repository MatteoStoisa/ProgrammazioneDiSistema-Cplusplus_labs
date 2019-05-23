#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include <memory>

#include "Symbol.h"
#include "Message.h"

class SharedEditor {
private:
public:
    SharedEditor();
    ~SharedEditor();

    int idSharedEditor;
    void receiveMessage(Message);

};


#endif
