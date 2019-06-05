#ifndef LAB4_JOBSCHEDULER_H
#define LAB4_JOBSCHEDULER_H

#include <queue>

#include "Job.h"
#include "Worker.h"

class JobScheduler {
private:
public:
    JobScheduler();
    ~JobScheduler();

    std::priority_queue<Job,std::vector<Job>,std::less<Job>> job_priorityQueue;
    std::queue<Job,std::vector<Job>> jobInAct_queue;
    std::vector<Job> jobTerminated_vector;

    std::vector<Worker> workerThread_vector;

};


#endif