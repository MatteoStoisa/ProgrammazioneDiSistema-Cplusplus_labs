#include <thread>
#include <iostream>
#include <mutex>

#include "JobScheduler.h"

int simulator_time = 300;
int threads = 8;
std::mutex extern output_mutex;

void effe() {
  output_mutex.lock();
  std::cout<<"Worker thread started at PID "<<std::this_thread::get_id()<<"\n";
  output_mutex.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(10));
}

JobScheduler::JobScheduler() {
}

JobScheduler::~JobScheduler() {
  for(auto it = this->thread_vector.begin(); it != this->thread_vector.end(); ++it) {
    it->join();
  }
}

void JobScheduler::submit (Job j) {
  this->job_priorityQueue.push(j);
}

void JobScheduler::start() {
  for(int i = 0;i < threads; i++) {
    this->thread_vector.push_back(std::thread(effe));
  }
}