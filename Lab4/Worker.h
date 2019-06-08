#ifndef LAB4_WORKER_H
#define LAB4_WORKER_H

#include <thread>
#include <iostream>
#include <vector>

class Worker {
private:
public:
    Worker();
    ~Worker();

    int id;

    void beginWork();
};

#endif
