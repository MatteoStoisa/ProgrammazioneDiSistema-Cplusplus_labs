#include "Job.h"

int extern idGenerator_Job;

Job::Job() {
  this->id = idGenerator_Job++;
  this->execution_time = 0;
  this->wait_time = 0;
}

Job::~Job() = default;
