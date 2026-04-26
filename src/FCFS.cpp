#include "../include/FCFS.h"
#include <iostream>
using namespace std;

void FCFS::schedule()
{
    cout << "\n=== FCFS SCHEDULING ===\n";

    processList->sortByArrivalTime();

    int currentTime = 0;
    Node *node = processList->getHead();

    while (node != nullptr)
    {
        Process *temp = node->data;
        if (currentTime < temp->arrivalTime)
        {
            currentTime = temp->arrivalTime;
        }
        cpu.loadProcess(temp, currentTime);
        gantt.add(temp->pid, currentTime, currentTime + temp->burstTime);
        cpu.execute();
        currentTime = cpu.getCurrentTime();
        cpu.unloadProcess();

        node = node->next;
    }

    displayResults();
}