#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <atomic>

#include "JobScheduler.h"
#include "time.h"

extern int threads;
extern int simulator_time;
extern double getTime(std::chrono::time_point<std::chrono::system_clock>);

extern std::mutex output_mutex;
extern std::mutex time_mutex;

double getTime(std::chrono::time_point<std::chrono::system_clock> start) {
  time_mutex.lock();
  std::chrono::time_point<std::chrono::system_clock> checkTime = std::chrono::system_clock::now();
  time_mutex.unlock();
  std::chrono::duration<double> durationTime = checkTime - start;
  return durationTime.count();
}

JobScheduler::JobScheduler() {
  this->startTime = std::chrono::system_clock::now();
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
  double diff = j.start_time - (getTime(this->startTime) * 1000);
  if(j.start_time == 0 || (diff < 0)) {
    jobInAct_queue_mutex.lock();
    this->jobInAct_queue.push(j);
    jobInAct_queue_mutex.unlock();
    j.lastUpdated = std::chrono::system_clock::now();
    output_mutex.lock();
    std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Job "<<j.id<<" ("<<j.duration<<" ms) ready after "<<j.start_time<<" ms"<<std::endl;
    output_mutex.unlock();
  }
  else {
    this->job_vector_mutex.lock();
    this->job_vector.push_back(j);
    this->job_vector_mutex.unlock();
    std::thread t(&JobScheduler::waitToSubmit,this,j,diff);
    t.detach();
  }
}

void JobScheduler::waitToSubmit(Job j,double diff) { //TODO: doesnt work thread+detach?
    std::this_thread::sleep_for(std::chrono::milliseconds((long int) diff));
    this->job_vector_mutex.lock();
    for(auto it = this->job_vector.begin(); it != this->job_vector.end(); ++it) {
        if(j == *it) {
            this->job_vector.erase(it);
            break;
        }
    }
    j.lastUpdated = std::chrono::system_clock::now();
    this->job_vector_mutex.unlock();
    this->jobInAct_queue_mutex.lock();
    this->jobInAct_queue.push(j);
    this->jobInAct_queue_mutex.unlock();
    output_mutex.lock();
    std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Job "<<j.id<<" ("<<j.duration<<" ms) ready after "<<j.start_time<<" ms"<<std::endl;
    output_mutex.unlock();
}

void JobScheduler::mainWorkingThreadFunction_aka_EFFE() {
  int waitCounter = 0;
  output_mutex.lock();
  std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Thread "<<std::this_thread::get_id()<<" started"<<std::endl;
  output_mutex.unlock();
  while(1) {
    if(this->job_vector.empty() && this->jobInAct_queue.empty() && (this->anyWorking == 0)) { //termination condition
      output_mutex.lock();
      std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Thread "<<std::this_thread::get_id()<<" end for inactivity"<<std::endl;
      output_mutex.unlock();
      break;
    }
    else { //take job from queue with mutex
      if(!this->jobInAct_queue.empty()) {
        if(waitCounter != 0)
          waitCounter = 0;
        this->jobInAct_queue_mutex.lock();
        Job jobWorking = this->jobInAct_queue.top();
        this->jobInAct_queue.pop();
        this->anyWorking++;
        this->jobInAct_queue_mutex.unlock();
        jobWorking.wait_time += std::chrono::system_clock::now() - jobWorking.lastUpdated;
        if(jobWorking.duration > simulator_time) { //work
          output_mutex.lock();
          std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Thread "<<std::this_thread::get_id()<<" -> Job "<<jobWorking.id<<" ["<<jobWorking.execution_time<<"/"<<jobWorking.duration<<"]"<<std::endl;
          output_mutex.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(simulator_time));
          jobWorking.duration -= simulator_time;
          jobWorking.execution_time += simulator_time;
          jobWorking.lastUpdated = std::chrono::system_clock::now();
          this->jobInAct_queue_mutex.lock();
          this->jobInAct_queue.push(jobWorking);
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
        else {
          output_mutex.lock();
          jobWorking.execution_time += jobWorking.duration;
          std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Thread "<<std::this_thread::get_id()<<" end Job "<<jobWorking.id<<" ["<<jobWorking.execution_time<<"/"<<jobWorking.duration<<"] waited "<<jobWorking.wait_time.count()<<" s"<<std::endl;
          output_mutex.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(jobWorking.duration));
          jobWorking.duration = 0;
          jobWorking.completation_time = getTime(this->startTime);
          this->jobTerminated_vector.push_back(jobWorking);
          this->jobInAct_queue_mutex.lock();
          this->anyWorking--;
          this->jobInAct_queue_mutex.unlock();
        }
      }
      else { //no job ready to execute, wait for start_time //TODO: implement condition_variable to sleep and being awake
        waitCounter++;
        output_mutex.lock();
        std::cout<<"<"<<getTime(this->startTime)<<std::showpoint<<"> "<<"Thread "<<std::this_thread::get_id()<<" on wait ["<<waitCounter<<"]"<<std::endl;
        output_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(simulator_time));
        //this->jobInAct_conditionVariable.wait_until();
      }
    }
  }
}
