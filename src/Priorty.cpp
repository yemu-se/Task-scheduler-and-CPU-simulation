#include "../include/Priority.h"
#include <iostream>
#include <climits>

using namespace std;

Priority::Priority(bool preemtiveMode)
{
    preemptive = preemtiveMode;
}

void Priority::schedule()
{
    cout << "\n=== PRIORITY SCHEDULING (" << (preemptive ? "Preemptive" : "Non-Preemptive") << ") ===\n";

    Process *processes[100];
    int processCount = 0;
    Process *temp = processList->getHead();
    while (temp != nullptr)
    {
        processes[processCount++] = temp;
        temp = temp->next;
    }

    for (int i = 0; i < processCount - 1; i++)
    {
        for (int j = 0; j < processCount - i - 1; j++)
        {
            if (processes[j]->arrivalTime > processes[j + 1]->arrivalTime)
            {
                swap(processes[j], processes[j + 1]);
            }
        }
    }

    for (int i = 0; i < processCount; i++)
    {
        processes[i]->remainingTime = processes[i]->burstTime;
    }

    Process *readyQueue[100];
    int readyCount = 0;
    int currentTime = 0;
    int completed = 0;
    int index = 0;
    Process *runningProcess = nullptr;
    while (completed < processCount)
    {
        while (index < processCount && processes[index]->arrivalTime <= currentTime)
        {
            readyQueue[readyCount++] = processes[index];
            index++;
        }

        if (preemptive && runningProcess != nullptr && readyCount > 0)
        {
            int highestPriorityIndex = 0;

            for (int i = 1; i < readyCount; i++)
            {
                if (readyQueue[i]->priority < readyQueue[highestPriorityIndex]->priority)
                {
                    highestPriorityIndex = i;
                }
            }
            if (readyQueue[highestPriorityIndex]->priority < runningProcess->priority)
            {
                cpu.preempt();
                readyQueue[readyCount++] = runningProcess;
                runningProcess = nullptr;
            }
        }
        if (runningProcess == nullptr && readyCount > 0)
        {
            int highestPriortyIndex = 0;
            for (int i = 0; i < readyCount; i++)
            {
                if (readyQueue[i]->priority < readyQueue[highestPriortyIndex]->priority)
                {
                    highestPriortyIndex = i;
                }
            }
            runningProcess = readyQueue[highestPriortyIndex];
            for (int i = highestPriortyIndex; i < readyCount - 1; i++)
            {
            }
            readyCount--;
            int starttime = currentTime;
            cpu.loadProcess(runningProcess, starttime);
            gantt.add(runningProcess->pid, starttime, starttime + runningProcess->remainingTime);
            cpu.execute();
            currentTime = cpu.currentTime;
            if (runningProcess->remainingTime == 0)
            {
                cpu.unloadProcess();
                completed++;
                runningProcess = nullptr;
            }
        }
        else if (index < processCount)
        {
            currentTime = processes[index]->arrivalTime;
        }
    }
    displayResults();
}
