#include "../include/Process.h"
#include <iostream>

Process::Process(int id, int at, int bt, int pr)
{
    pid = id;
    arrivalTime = at;
    burstTime = bt;
    priority = pr;

    // execution state
    remainingTime = bt;

    // performance metrics
    waitingTime = 0;
    turnaroundTime = 0;
    completionTime = 0;
    responseTime = 0;
    firstResponseTime = -1; //-1 means "not yet responded
}