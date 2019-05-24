#ifndef LAB3_SHAREDEDITOR_H
#define LAB3_SHAREDEDITOR_H

#include <memory>
#include <list>

#include "Symbol.h"
#include "Message.h"
#include "NetworkServer.h"

class NetworkServer;

class SharedEditor {
private:
    NetworkServer& _server;
    int _siteId;
    std::list<Symbol> _symbols;
    int _counter;
public:
    SharedEditor(NetworkServer&);
    ~SharedEditor();

    int getIdScharedEditor();
    int getCounterSharedEditor();
    void incrementCounterSharedEditor();
    void setIdSharedEditor(int);

    void initCRDT();

    void localInsert(int,char);
    void localErase(int);
    std::string to_string();
    void process(const Message&);
    };


#endif
