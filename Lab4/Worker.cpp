#include "Worker.h"

int idGenerator_Worker = 0;

Worker::Worker() {
  this->id = idGenerator_Worker++;

}

Worker::~Worker() {
}

