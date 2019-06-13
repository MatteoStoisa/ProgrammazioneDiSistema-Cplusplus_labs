#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>

#include "JobScheduler.h"
#include "time.h"

int threads = 4;
int simulator_time = 2000;

std::mutex extern output_mutex;

extern std::string now_str();

JobScheduler::JobScheduler() {
  this->startTime = std::chrono::system_clock();
}

JobScheduler::~JobScheduler() {
  for(auto it = this->thread_vector.begin(); it != this->thread_vector.end(); ++it) {
    it->join();
  }
}

void JobScheduler::submit (Job j) {
  if(j.start_time == 0) {
    jobInAct_queue_mutex.lock();
    this->jobInAct_queue.push(j);
    jobInAct_queue_mutex.unlock();
  }
  else {
    this->job_vector_mutex.lock();
    this->job_vector.push_back(j);
    this->job_vector_mutex.unlock();
    std::thread t(&JobScheduler::waitToSubmit,this,j);
    t.detach();
  }
}

void JobScheduler::start() {
    for(int i = 0;i < threads; i++) {
        this->thread_vector.push_back(std::thread(&JobScheduler::effe,this));
    }
}

void JobScheduler::effe() {
  output_mutex.lock();
  std::cout<<"Thread "<<std::this_thread::get_id()<<" started"<<std::endl;
  output_mutex.unlock();
  while(1) {
    if(this->job_vector.empty() && this->jobInAct_queue.empty() && (this->anyWorking == 0)) { //termination condition
      output_mutex.lock();
      std::cout<<"Thread "<<std::this_thread::get_id()<<" end for inactivity"<<std::endl;
      output_mutex.unlock();
      break;
    }
    else { //take job from queue with mutex
      if(!this->jobInAct_queue.empty()) {
        this->jobInAct_queue_mutex.lock();
        Job jobWorking = this->jobInAct_queue.top();
        this->jobInAct_queue.pop();
        this->anyWorking++;
        this->jobInAct_queue_mutex.unlock();
        if(jobWorking.duration > simulator_time) { //work
          output_mutex.lock();
          std::cout<<"Thread "<<std::this_thread::get_id()<<" on job "<<jobWorking.id<<": "<<jobWorking.duration<<" remaining (-"<<simulator_time<<")"<<std::endl;
          output_mutex.unlock();
          std::this_thread::__sleep_for(std::chrono::seconds(simulator_time/1000),std::chrono::nanoseconds(0));
          jobWorking.duration -= simulator_time;
          this->jobInAct_queue_mutex.lock();
          this->jobInAct_queue.push(jobWorking);
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
        else {
          output_mutex.lock();
          std::cout<<"Thread "<<std::this_thread::get_id()<<" on job "<<jobWorking.id<<": "<<jobWorking.duration<<" remaining, end (-"<<simulator_time<<")"<<std::endl;
          output_mutex.unlock();
          std::this_thread::__sleep_for(std::chrono::seconds(jobWorking.duration/1000),std::chrono::nanoseconds(0));
          jobWorking.duration = 0;
          this->jobTerminated_vector.push_back(jobWorking);
          this->jobInAct_queue_mutex.lock();
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
      }
      else { //no job ready to execute, wait for start_time
        output_mutex.lock();
        std::cout<<"Thread "<<std::this_thread::get_id()<<" on wait"<<std::endl;
        output_mutex.unlock();
        std::this_thread::__sleep_for(std::chrono::seconds(5),std::chrono::nanoseconds(0));
      }
    }
  }
}

void JobScheduler::waitToSubmit(Job j) { //TODO: doesnt work thread+detach?
  std::this_thread::__sleep_for(std::chrono::seconds(j.start_time/1000),std::chrono::nanoseconds(0));
  this->job_vector_mutex.lock();
  for(auto it = this->job_vector.begin(); it != this->job_vector.end(); ++it) {
    if(j == *it) {
      this->job_vector.erase(it);
      break;
    }
  }
  this->job_vector_mutex.unlock();
  this->jobInAct_queue_mutex.lock();
  this->jobInAct_queue.push(j);
  this->jobInAct_queue_mutex.unlock();
}
