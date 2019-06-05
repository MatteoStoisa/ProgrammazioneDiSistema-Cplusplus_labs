#include "Worker.h"

int idGenerator_Worker = 0;


void effe() {
  std::cout<<"Worker thread started at PID "<<std::this_thread::get_id()<<"\n";
  //while(1) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
  //}
}

Worker::Worker() {
  this->id = idGenerator_Worker++;

  std::thread workerThread(effe);
  workerThread.detach();
}

Worker::~Worker() {
}

