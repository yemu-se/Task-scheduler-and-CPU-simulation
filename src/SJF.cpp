#include "../include/SJF.h"
#include <iostream>
#include <climits>
using namespace std;

void SJF::schedule()
{
    cout << "\n=== SJF SCHEDULING (Preemptive Shortest Remaining Time) ===\n";
    Process *proceses[100];
    int processCount = 0;
    Node *node = processList->getHead();

    while (node != nullptr)
    {
        proceses[processCount++] = node->data;
        node = node->next;
    }

    for (int i = 0; i < processCount - 1; i++)
    {
        for (int j = 0; j < processCount - i - 1; j++)
        {
            if (proceses[j]->arrivalTime > proceses[j + 1]->arrivalTime)
            {
                swap(proceses[j], proceses[j + 1]);
            }
        }
    }
    for (int i = 0; i < processCount; i++)
    {
        proceses[i]->remainingTime = proceses[i]->burstTime;
    }
    MinHeap readyQueue;
    int currentTime = 0;
    int completed = 0;
    int index = 0;
    Process *currentProcess = nullptr;

    while (completed < processCount)
    {
        while (index < processCount && proceses[index]->arrivalTime <= currentTime)
        {
            readyQueue.insert(proceses[index]);
            index++;
        }

        if (currentProcess == nullptr && !readyQueue.isEmpty())
        {
            currentProcess = readyQueue.extractMin();
        }

        if (currentProcess == nullptr)
        {
            if (index < processCount)
            {
                currentTime = proceses[index]->arrivalTime;
            }
            continue;
        }

        int nextArrivalTime = (index < processCount) ? proceses[index]->arrivalTime : INT_MAX;
        int executeTime = min(currentProcess->remainingTime, nextArrivalTime - currentTime);
        if (executeTime <= 0)
        {
            currentTime = nextArrivalTime;
            continue;
        }

        cpu.loadProcess(currentProcess, currentTime);
        gantt.add(currentProcess->pid, currentTime, currentTime + executeTime);
        cpu.execute(executeTime);
        currentTime = cpu.getCurrentTime();

        if (currentProcess->remainingTime == 0)
        {
            cpu.unloadProcess();
            completed++;
            currentProcess = nullptr;
        }
        else
        {
            cpu.preempt();
            readyQueue.insert(currentProcess);
            currentProcess = nullptr;
        }
    }
    displayResults();
}