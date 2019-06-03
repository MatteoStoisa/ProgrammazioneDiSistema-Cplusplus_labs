#include "Worker.h"

int idGenerator_Worker = 0;

void f() {

}

Worker::Worker() {
  this->id = idGenerator_Worker++;
  std::thread t(f);
}

Worker::~Worker() {

}


