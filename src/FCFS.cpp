#include "../include/FCFS.h"
#include <iostream>
using namespace std;

void FCFS::schedule()
{
    cout << "\n=== FCFS SCHEDULING ===\n";

    processList->sortByArrivalTime();

    int currentTIme = 0;
    Process *temp = processList->getHead();

    while (temp != nullptr)
    {
        if (currentTIme < temp->arrivalTime)
        {
            currentTIme = temp->arrivalTime;
        }
        cpu.loadProcess(temp, currentTIme);
        gantt.add(temp->pid, currentTIme, currentTIme + temp->burstTime);
        cpu.execute();
        currentTIme = cpu.getCurrentTime();
        cpu.unloadProcess();

        temp = temp->next;
    }

    displayResults();
}