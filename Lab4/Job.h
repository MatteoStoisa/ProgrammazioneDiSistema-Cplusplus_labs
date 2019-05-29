#ifndef LAB4_JOB_H
#define LAB4_JOB_H

#include <chrono>

class Job {
private:

public:
    int id;
    std::chrono::duration<int, std::milli> duration;
    std::chrono::duration<int, std::milli> execution_time;
    std::chrono::duration<int, std::milli> wait_time;
    std::chrono::time_point<std::chrono::system_clock> completation_time;
    std::chrono::time_point<std::chrono::system_clock> start_time;

    Job();
    ~Job();

};

bool operator<(const Job&, const Job&);

#endif
