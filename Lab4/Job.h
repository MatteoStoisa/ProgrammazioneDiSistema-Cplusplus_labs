#ifndef LAB4_JOB_H
#define LAB4_JOB_H


class Job {
private:
    int id;
    long int duration;
    long int execution_time;
    long int wait_time;
    long int completation_time;
public:
    static long int start_time;

    Job();
    ~Job();
};


#endif
