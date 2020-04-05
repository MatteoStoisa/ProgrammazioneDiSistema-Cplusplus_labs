#include "Job.h"

Job::Job(int i,long int start,long int dur) {
  this->id = i;
  this->duration = dur;
  this->execution_time = 0;
  this->wait_time = std::chrono::duration<double>(0);
  this->start_time = start;
}

Job::~Job() = default;

bool operator<(const Job& joba, const Job& jobb) {
    return (joba.lastUpdated < jobb.lastUpdated); //TODO: FIFO order of jobInAct_queue (?)
}

bool Job::operator==(Job j) {
  if(this->start_time != j.start_time)
    return false;
  if(this->duration != j.duration)
    return false;
  if(this->wait_time != j.wait_time)
    return false;
  if(this->completation_time != j.completation_time)
    return false;
  return true;
}
