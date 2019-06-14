#include <iostream>
#include <chrono>

#include "Job.h"
#include "JobScheduler.h"

#include <unistd.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>

int threads = 4;
int simulator_time = 200;

std::mutex output_mutex;
std::mutex time_mutex;

std::chrono::time_point<std::chrono::system_clock> startTime, checkTime;

double getTime() {
  time_mutex.lock();
  checkTime = std::chrono::system_clock::now();
  time_mutex.unlock();
  std::chrono::duration<double> durationTime = checkTime - startTime;
  return durationTime.count();
}

int main() {
  startTime = std::chrono::system_clock::now();
  std::cout<<"--- Lab4 ---\n<"<<getTime()<<std::showpoint<<"> Main "<<std::this_thread::get_id()<<", "<<threads<<" core, "<<simulator_time<<" ms"<<std::endl;


  JobScheduler p{};
  p.submit( Job ( 1 , 0 , 15000 )); // Job(int id, int start_time, int duration)
  p.submit( Job ( 2 , 0 , 6000 ));
  p.submit( Job ( 3 , 1000 , 9000 ));
  p.submit( Job ( 4 , 2000 , 12000 ));
  p.submit( Job ( 5 , 3000 , 16000 ));
  p.submit( Job ( 6 , 3000 , 5000 ));
  p.submit( Job ( 7 , 4000 , 7000 ));
  p.submit( Job ( 8 , 4000 , 6000 ));
  p.submit( Job ( 9 , 5000 , 9000 ));

    /*p.submit( Job ( 1 , 0 , 15000 )); // Job(int id, int start_time, int duration)
    p.submit( Job ( 2 , 56 , 6000 ));
    p.submit( Job ( 3 , 1000 , 9000 ));
    p.submit( Job ( 4 , 2000 , 12000 ));
    p.submit( Job ( 5 , 8000 , 16000 ));
    p.submit( Job ( 6 , 3000 , 5000 ));
    p.submit( Job ( 7 , 4000 , 7000 ));
    p.submit( Job ( 8 , 4000 , 6500 ));
    p.submit( Job ( 9 , 5000 , 9000 ));
    p.submit( Job ( 10 , 0 , 15000 )); // Job(int id, int start_time, int duration)
    p.submit( Job ( 20 , 0 , 6000 ));
    p.submit( Job ( 30 , 100 , 9000 ));
    p.submit( Job ( 40 , 2000 , 12000 ));
    p.submit( Job ( 50 , 30040 , 16050 ));
    p.submit( Job ( 60 , 3500 , 5000 ));
    p.submit( Job ( 70 , 4600 , 7050 ));
    p.submit( Job ( 80 , 4006 , 6000 ));
    p.submit( Job ( 90 , 5050 , 9000 ));
    p.submit( Job ( 11 , 0 , 15000 )); // Job(int id, int start_time, int duration)
    p.submit( Job ( 21 , 56 , 6000 ));
    p.submit( Job ( 31 , 1000 , 9000 ));
    p.submit( Job ( 41 , 2000 , 12000 ));
    p.submit( Job ( 51 , 8000 , 17000 ));
    p.submit( Job ( 61 , 3000 , 5000 ));
    p.submit( Job ( 71 , 4700 , 7070 ));
    p.submit( Job ( 81 , 4000 , 6500 ));
    p.submit( Job ( 91 , 5070 , 970 ));
    p.submit( Job ( 101 , 0 , 15700 )); // Job(int id, int start_time, int duration)
    p.submit( Job ( 201 , 0 , 6000 ));
    p.submit( Job ( 301 , 100 , 9000 ));
    p.submit( Job ( 401 , 2000 , 12000 ));
    p.submit( Job ( 501 , 30040 , 16050 ));
    p.submit( Job ( 601 , 3500 , 5000 ));
    p.submit( Job ( 701 , 4600 , 7070 ));
    p.submit( Job ( 801 , 4706 , 6700 ));
    p.submit( Job ( 901 , 5050 , 9000 ));*/

  p.start();



  while(1) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if(p.job_vector.empty() && p.jobInAct_queue.empty() && (p.anyWorking == 0))
      break;
  }

  std::cout<<"<"<<getTime()<<std::showpoint<<"> "<<"Main end"<<std::endl;
  return 0;
}
