#include "../include/Scheduler.h"
#include <iostream>
#include <iomanip>
using namespace std;

Scheduler::Scheduler()
{
    processList = new LinkedList();
    totalWaitingTime = 0;
    totalTurnaroundTime = 0;
    totalResponseTime = 0;
}

Scheduler::~Scheduler()
{
    delete processList;
}

void Scheduler::addProcess(int pid, int at, int bt, int pr)
{
    Process *p = new Process(pid, at, bt, pr);
    processList->insert(p);
}

void Scheduler::displayResults()
{
    gantt.display();

    cout << "\n"
         << string(120, '-') << endl;
    cout << "PROCESS DETAILS" << endl;
    cout << string(120, '-') << endl;
    cout << left << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(15) << "Burst"
         << setw(20) << "Completion"
         << setw(20) << "Turnaround"
         << setw(15) << "Waiting"
         << setw(15) << "Response" << endl;
    cout << string(120, '-') << endl;

    Process *temp = processList->getHead();
    int n = 0;
    totalWaitingTime = 0; // ← FIXED
    totalTurnaroundTime = 0;
    totalResponseTime = 0;

    while (temp != nullptr)
    {
        cout << left << setw(10) << ("P" + to_string(temp->pid))
             << setw(15) << temp->arrivalTime
             << setw(15) << temp->burstTime
             << setw(20) << temp->completionTime
             << setw(20) << temp->turnaroundTime
             << setw(15) << temp->waitingTime
             << setw(15) << temp->responseTime << endl;

        totalWaitingTime += temp->waitingTime; // ← FIXED
        totalTurnaroundTime += temp->turnaroundTime;
        totalResponseTime += temp->responseTime;
        n++;
        temp = temp->next;
    }

    cout << string(120, '-') << endl;

    if (n > 0)
    {
        cout << fixed << setprecision(2);
        cout << "\nSTATISTICS:" << endl;
        cout << string(50, '-') << endl;
        cout << "Average Waiting Time:    " << totalWaitingTime / n << endl; // ← FIXED
        cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
        cout << "Average Response Time:   " << totalResponseTime / n << endl;
    }
}