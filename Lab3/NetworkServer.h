#ifndef LAB3_NETWORKSERVER_H
#define LAB3_NETWORKSERVER_H

#include <vector>
#include <map>
#include <memory>

#include "SharedEditor.h"
#include "Message.h"

class SharedEditor;

class NetworkServer {
private:
    std::map<int,std::shared_ptr<SharedEditor>> sharedEditorPointers;

    int idSharedEditorGenerator;
public:
    NetworkServer();
    ~NetworkServer();

    std::vector<Message> messageVector;

    int generateIdSharedNetwork();
    void incrementSharedEditor();

    int connect(SharedEditor*);
    void disconnect(SharedEditor*);
    void send(const Message&);
    void dispatchMessages();
};


#endif
