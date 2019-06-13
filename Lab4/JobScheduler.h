#ifndef LAB4_JOBSCHEDULER_H
#define LAB4_JOBSCHEDULER_H

#include <queue>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>

#include "Job.h"
//#include "Worker.h"

class JobScheduler {
private:
public:
    JobScheduler();
    ~JobScheduler();

    std::chrono::system_clock startTime;
    int anyWorking = 0; //same mutex as jobInAct

    std::vector<Job> job_vector;
    std::priority_queue<Job,std::vector<Job>,std::less<Job>> jobInAct_queue; //unneeded priority
    std::vector<Job> jobTerminated_vector;

    std::vector<std::thread> thread_vector;

    std::condition_variable job_priorityQueue_conditionVariable;
    std::mutex jobInAct_queue_mutex;
    std::mutex job_vector_mutex;

    void submit(Job);
    void start();

    void waitToSubmit(Job);
    void effe();
};


#endif