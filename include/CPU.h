#ifndef CPU_H
#define CPU_H

#include "Process.h"

struct CPU
{
    int currentTime;
    Process* runningProcess;

    CPU();
    int getCurrentTime();
    bool isIdle();
    void loadProcess(Process* p, int startTime);
    void unloadProcess();
        void preempt();
    int execute(int timeQuantum = -1);

};
#endif