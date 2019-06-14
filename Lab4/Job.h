#ifndef LAB4_JOB_H
#define LAB4_JOB_H

#include <chrono>

class Job {
private:

public:
    int id;
    long int duration;
    long int execution_time;
    std::chrono::duration<double> wait_time;
    long int completation_time; //TODO: scope for this variable??
    long int start_time;

    std::chrono::time_point<std::chrono::system_clock> lastUpdated;

    Job(int,long int,long int);
    ~Job();

    bool operator==(Job);

};

bool operator<(const Job&, const Job&);

#endif
