#ifndef LAB4_JOBSCHEDULER_H
#define LAB4_JOBSCHEDULER_H

#include <queue>
#include <thread>
#include <iostream>
#include <vector>

#include "Job.h"
//#include "Worker.h"

class JobScheduler {
private:
public:
    JobScheduler();
    ~JobScheduler();

    std::priority_queue<Job,std::vector<Job>,std::less<Job>> job_priorityQueue;
    std::queue<Job,std::vector<Job>> jobInAct_queue;
    std::vector<Job> jobTerminated_vector;

    //std::vector<Worker> worker_vector;
    std::vector<std::thread> thread_vector;

    void submit(Job);
    void start();

};


#endif