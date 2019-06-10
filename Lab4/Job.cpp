#include "Job.h"

int idGenerator_Job = 0;

Job::Job(int i,long int start,long int dur) {
  //this->id = idGenerator_Job++;
  this->id = i;
  this->duration = dur;
  this->execution_time = 0;
  this->wait_time = 0;
  this->start_time = start;
}

Job::~Job() = default;

bool operator<(const Job& joba, const Job& jobb) {
    return (joba.start_time < jobb.start_time);
}
