#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include <memory>

#include "Symbol.h"
#include "Message.h"

class SharedEditor {
private:
    int idSharedEditor;
public:
    SharedEditor();
    ~SharedEditor();

    int getCodScharedEditor();
    void getMessage(Message);
};


#endif
