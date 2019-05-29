#ifndef LAB4_JOBSCHEDULER_H
#define LAB4_JOBSCHEDULER_H


#include <queue>

#include "Job.h"

#define simulator_time 500;

class JobScheduler {
private:
    std::priority_queue<Job,std::vector<Job>,std::less<Job>> job_priorityQueue;
    std::queue<Job,std::vector<Job>> jobInAct_queue;
    std::vector<Job> jobTerminated_vector;
public:
    JobScheduler();
    ~JobScheduler();
};


#endif