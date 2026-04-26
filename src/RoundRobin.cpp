#include "../include/RoundRobin.h"
#include <iostream>
#include <climits>

RoundRobin::RoundRobin(int tq) : timeQuantum(tq) {}

void RoundRobin::schedule()
{
    cout << "\n=== ROUND ROBIN SCHEDULING (Quantum = " << timeQuantum << ") ===\n";
    Process *processes[100];
    int processCount = 0;
    Node *node = processList->getHead();
    while (node != nullptr)
    {
        processes[processCount++] = node->data;
        node = node->next;
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

    Queue readQueue;
    int currentTime = 0;
    int completed = 0;
    int index = 0;

    while (completed < processCount)
    {
        while (index < processCount && processes[index]->arrivalTime <= currentTime)
        {
            readQueue.enqueue(processes[index]);
            index++;
        }

        if (readQueue.isEmpty())
        {
            if (index < processCount)
            {
                currentTime = processes[index]->arrivalTime;
                continue;
            }
            break;
        }

        Process *current = readQueue.dequeue();
        int executeTime = (timeQuantum < current->remainingTime) ? timeQuantum : current->remainingTime;

        int startTime = currentTime;
        cpu.loadProcess(current, startTime);
        cpu.execute(executeTime);
        currentTime = cpu.getCurrentTime();

        gantt.add(current->pid, startTime, currentTime);

        if (current->remainingTime == 0)
        {
            cpu.unloadProcess();
            completed++;
        }
        else
        {
            cpu.preempt();
            while (index < processCount && processes[index]->arrivalTime <= currentTime)
            {
                readQueue.enqueue(processes[index]);
                index++;
            }
            readQueue.enqueue(current);
        }
    }
    displayResults();
}