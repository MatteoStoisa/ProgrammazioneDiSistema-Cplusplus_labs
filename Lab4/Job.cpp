#include "Job.h"

int extern idGenerator_Job;

Job::Job() {
  this->id = idGenerator_Job++;
  //this->duration =
  this->execution_time = std::chrono::milliseconds(0);
  this->wait_time = std::chrono::milliseconds(0);
  this->start_time = std::chrono::system_clock::now();
}

Job::~Job() = default;

bool operator<(const Job& joba, const Job& jobb) {
    return (joba.start_time < jobb.start_time);
}
