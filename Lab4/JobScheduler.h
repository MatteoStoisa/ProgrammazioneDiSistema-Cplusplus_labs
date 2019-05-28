#ifndef LAB4_JOBSCHEDULER_H
#define LAB4_JOBSCHEDULER_H


#include <queue>

#include "Job.h"

class JobScheduler {
private:
    std::priority_queue<Job,std::vector<Job>,std::less<Job::start_time>>;
public:
    JobScheduler();
    ~JobScheduler();
};


#endif