#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>

#include "JobScheduler.h"

int simulator_time = 300;
int threads = 8;

std::mutex extern output_mutex;

void effe(JobScheduler js) {
  output_mutex.lock();
  std::cout<<"Worker thread started at PID "<<std::this_thread::get_id()<<"\n";
  output_mutex.unlock();
  while(1) {
    if(js.job_priorityQueue.empty() && js.jobInAct_queue.empty()) { //termination condition
      break;
    }
    else { //take job from queue with mutex
      if(!js.jobInAct_queue.empty()) {
        js.jobInAct_queue_mutex.lock();
        //Job jobWorking = this->jobInAct_queue.front();
        Job jobWorking = js.jobInAct_queue.top();
        //this->jobInAct_queue.pop(); //TODO: pop doesnt work (?)
        js.jobInAct_queue_mutex.unlock();
        if(jobWorking.duration > simulator_time) { //work
          output_mutex.lock();
          std::cout<<"job "<<jobWorking.id<<"working: "<<jobWorking.duration<<" remaning";
          std::this_thread::__sleep_for(std::chrono::seconds(simulator_time/1000),std::chrono::nanoseconds(0));
          jobWorking.duration -= simulator_time;
          js.jobInAct_queue_mutex.lock();
          js.jobInAct_queue.push(jobWorking);
          js.jobInAct_queue_mutex.unlock();
        }
        else {
          std::this_thread::__sleep_for(std::chrono::seconds(jobWorking.duration/1000),std::chrono::nanoseconds(0));
          jobWorking.duration = 0;
          js.jobTerminated_vector.push_back(jobWorking);
        }
      }
      else { //no job ready to execute, wait for start_time
        std::this_thread::__sleep_for(std::chrono::seconds(js.job_priorityQueue.top().start_time/1000),std::chrono::nanoseconds(0));
        //TODO: continue here
      }
    }
  }

}

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
  for(int i = 0;i < threads; i++) {
    this->thread_vector.push_back(std::thread(effe,this)); //TODO: how to call??
  }

}