#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>

#include "JobScheduler.h"


std::mutex extern output_mutex;



JobScheduler::JobScheduler() {
  this->startTime = std::chrono::system_clock();
}

JobScheduler::~JobScheduler() {
  for(auto it = this->thread_vector.begin(); it != this->thread_vector.end(); ++it) {
    //TODO: verify thread is not working on a Job
    it->join();
  }
}

void JobScheduler::submit (Job j) {
  this->job_priorityQueue.push(j);
}

void JobScheduler::start() {


}