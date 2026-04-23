#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LinkedList.h"
#include "CPU.h"
#include "GanttChart.h"

struct Scheduler
{
    LinkedList* processList;
    CPU cpu;
    GanttChart gantt;
    float totalWaitingTime;
     float totalTurnaroundTime;
     float totalResponseTime;

     Scheduler();
     ~Scheduler();

     void addProcess(int pid,int at,int bt,int pr=0);
     void displayResults();
virtual void schedule() = 0;
};
#endif