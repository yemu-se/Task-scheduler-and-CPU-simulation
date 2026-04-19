#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
using namespace std;

enum ProcessState
{
    NEW,
    READY,
    RUNNING,
    TERMINATED
};

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;

    // execution state
    int remainingTime;
    ProcessState state;

    // performance metrics
    int startTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int responseTime;
    int firstResponseTime;

    // constructor
    Process(int id = 0, int at = 0, int bt = 0, int pr = 0);

    // methods
    void reset();
    bool isCompleted() const;
    void display() const;
};
#endif