#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include <memory>
#include <ntsecapi.h>

#pragma once

//#include "NetworkServer.h"
#include "Symbol.h"
#include "Message.h"

class SharedEditor {
private:
    int idSharedEditor;
public:
    SharedEditor();
    ~SharedEditor();

    int getIdScharedEditor();
    void getMessage(Message);
    void setIdSharedEditor(int);
};


#endif
