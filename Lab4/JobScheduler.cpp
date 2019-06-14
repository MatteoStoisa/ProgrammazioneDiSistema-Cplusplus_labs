#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <atomic>

#include "JobScheduler.h"
#include "time.h"

int extern threads;
int extern simulator_time;

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

void JobScheduler::start() {
    for(int i = 0;i < threads; i++) {
        this->thread_vector.push_back(std::thread(&JobScheduler::mainWorkingThreadFunction_aka_EFFE,this));
    }
}

void JobScheduler::submit (Job j) {
  if(j.start_time == 0) {
    jobInAct_queue_mutex.lock();
    this->jobInAct_queue.push(j);
    jobInAct_queue_mutex.unlock();
    output_mutex.lock();
    std::cout<<"Job "<<j.id<<" ready after "<<j.start_time<<" ms"<<std::endl;
    output_mutex.unlock();
  }
  else {
    this->job_vector_mutex.lock();
    this->job_vector.push_back(j);
    this->job_vector_mutex.unlock();
    std::thread t(&JobScheduler::waitToSubmit,this,j);
    t.detach();
  }
}

void JobScheduler::waitToSubmit(Job j) { //TODO: doesnt work thread+detach?
    std::this_thread::sleep_for(std::chrono::milliseconds(j.start_time));
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
    output_mutex.lock();
    std::cout<<"Job "<<j.id<<" ready after "<<j.start_time<<" ms"<<std::endl;
    output_mutex.unlock();
}

void JobScheduler::mainWorkingThreadFunction_aka_EFFE() {
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
          std::cout<<"Thread "<<std::this_thread::get_id()<<" on Job "<<jobWorking.id<<": "<<jobWorking.duration<<" ms remaining"<<std::endl;
          output_mutex.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(simulator_time));
          jobWorking.duration -= simulator_time;
          jobWorking.execution_time += simulator_time;
          this->jobInAct_queue_mutex.lock();
          this->jobInAct_queue.push(jobWorking);
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
        else {
          output_mutex.lock();
          std::cout<<"Thread "<<std::this_thread::get_id()<<" on Job "<<jobWorking.id<<": "<<jobWorking.duration<<" ms remaining, end Job"<<std::endl;
          output_mutex.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(jobWorking.duration));
          jobWorking.execution_time += jobWorking.duration;
          jobWorking.duration = 0;
          this->jobTerminated_vector.push_back(jobWorking);
          this->jobInAct_queue_mutex.lock();
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
      }
      else { //no job ready to execute, wait for start_time //TODO: implement condition_variable to sleep and being awake
        output_mutex.lock();
        std::cout<<"Thread "<<std::this_thread::get_id()<<" on wait"<<std::endl;
        output_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(simulator_time));
        //this->jobInAct_conditionVariable.wait_until();
      }
    }
  }
}
