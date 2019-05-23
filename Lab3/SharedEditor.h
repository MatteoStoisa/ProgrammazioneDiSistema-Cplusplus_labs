#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include <memory>

#include "Symbol.h"
#include "Message.h"
#include "NetworkServer.h"

class NetworkServer;

class SharedEditor {
private:
    NetworkServer& _server;
    int _siteId;
    std::vector<Symbol> _symbols;
    int _counter;
public:
    SharedEditor(NetworkServer&);
    ~SharedEditor();

    int getIdScharedEditor();
    int getCounterSharedEditor();
    void incrementCounterSharedEditor();
    void setIdSharedEditor(int);

    void receiveMessage(Message);

    void initSRDT();

    void localInsert(int,char);

    std::vector<int> calculateNewSRDT(int, std::vector<Symbol>);
    };


#endif
