#include <thread>
#include <iostream>

#include "JobScheduler.h"

int simulator_time = 500;
int threads = 8;

JobScheduler::JobScheduler() {
  for(int i = 0;i < threads; i++) {
    workerThread_vector.push_back(Worker());
  }
}

JobScheduler::~JobScheduler() {
}