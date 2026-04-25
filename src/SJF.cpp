#include "../include/SJF.h"
#include <iostream>
#include <climits>
using namespace std;

void SJF::schedule()
{
    cout << "\n=== SJF SCHEDULING (Non-Preemptive) ===\n";
    Process *proceses[100];
    int processCount = 0;
    Process *temp = processList->getHead();

    while (temp != nullptr)
    {
        proceses[processCount++] = temp;
        temp = temp->next;
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
    MinHeap readQueue;
    int currentTime = 0;
    int completed = 0;
    int index = 0;

    while (completed < processCount)
    { // Load all processes that have arrived by "currentTime" into the MinHeap
        while (index < processCount && proceses[index]->arrivalTime <= currentTime)
        {
            readQueue.insert(proceses[index]);
            index++;
        }
        if (!readQueue.isEmpty())
        {
            Process *shortest = readQueue.extractMin();
            shortest->waitingTime = currentTime - shortest->arrivalTime;
            shortest->turnaroundTime = shortest->waitingTime + shortest->burstTime;
            if (currentTime < shortest->arrivalTime)
            {
                currentTime = shortest->arrivalTime;
            }

            cpu.loadProcess(shortest, currentTime);
            gantt.add(shortest->pid, currentTime, currentTime + shortest->remainingTime);
            cpu.execute();
            currentTime = cpu.getCurrentTime();
            cpu.unloadProcess();
            completed++;
        }
        else if (index < processCount)
        {
            currentTime = proceses[index]->arrivalTime;
        }
    }
    displayResults();
}