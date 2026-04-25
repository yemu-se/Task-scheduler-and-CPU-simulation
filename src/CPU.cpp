#include "../include/CPU.h"
#include <algorithm>
using namespace std;

CPU::CPU()
{
    currentTime = 0;
    runningProcess = nullptr;
}

int CPU::getCurrentTime()
{
    return currentTime;
}

bool CPU::isIdle()
{
    return runningProcess == nullptr;
}

void CPU::loadProcess(Process *p, int startTime)
{
    if (startTime > currentTime)
    {
        currentTime = startTime;
    }
    runningProcess = p;
    p->state = RUNNING;
    if (p->firstResponseTime == -1)
    {
        p->firstResponseTime = currentTime;
        p->responseTime = p->firstResponseTime - p->arrivalTime;
    }
}

void CPU::unloadProcess()
{
    if (runningProcess)
    {
        runningProcess->completionTime = currentTime;
        runningProcess->turnaroundTime = runningProcess->completionTime - runningProcess->arrivalTime;
        runningProcess->waitingTime = runningProcess->turnaroundTime - runningProcess->burstTime;
        runningProcess->state = TERMINATED;
        runningProcess = nullptr;
    }
    else{
        runningProcess = nullptr;
    }
}

void CPU::preempt()
{
    if (runningProcess)
    {
        runningProcess->state = READY;
        runningProcess = nullptr;
    }
}

int CPU::execute(int timeQuantum)
{
    if (!runningProcess)
        return 0;
    int executeTime;
    if (timeQuantum == -1)
    {
        executeTime = runningProcess->remainingTime;
    }
    else
    {
        executeTime = min(timeQuantum, runningProcess->remainingTime);
    }

    runningProcess->remainingTime -= executeTime;
    currentTime += executeTime;
    return executeTime;
}