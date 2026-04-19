#include <iostream>
#include "include/Process.h"
#include "include/GanttChart.h"

using namespace std;

void simulateFCFS(Process processes[], int n, GanttChart &gantt)
{
    int currentTime = 0;
    cout << "\n=== FCFS SIMULATION ===" << endl;
    cout << "Time\tAction" << endl;
    cout << "----\t------" << endl;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].arrivalTime)
        {
            cout << currentTime << "\tCPU idle until "
                 << processes[i].arrivalTime << endl;
            currentTime = processes[i].arrivalTime;
        }

        cout << currentTime << "\tP" << processes[i].pid << " starts";
        gantt.add(processes[i].pid, currentTime, currentTime + processes[i].burstTime);

        currentTime += processes[i].burstTime;
        cout << " -> completes at " << currentTime << endl;

        processes[i].completionTime = currentTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        processes[i].responseTime = processes[i].startTime - processes[i].arrivalTime;
    }
}

int main()
{
    cout << "\n========================================" << endl;
    cout << "CPU SCHEDULER - DAY 2" << endl;
    cout << "Gantt Chart & Timeline Visualization" << endl;
    cout << "========================================\n"
         << endl;

    // === PART 1: Understanding Gantt Chart ===
    cout << "=== PART 1: Basic Gantt Chart ===" << endl;


    GanttChart chart1;
    cout << "\nAdding execution blocks:\n";
    chart1.add(1, 0, 5);  // P1 runs from 0 to 5
    chart1.add(1, 6, 8);  // P2 runs from 5 to 8
    chart1.add(2, 5, 16); // P3 runs from 8 to 16

    chart1.display();

    // === PART 2: Merging Consecutive Blocks ===
    cout << "\n=== PART 2: Merging Same Process ===" << endl;

    GanttChart chart2;
    cout << "\nAdding blocks for same process:\n";
    chart2.add(1, 0, 3);  // P1 runs 0-3
    chart2.add(1, 3, 5);  // P1 continues 3-5 (should merge)
    chart2.add(2, 5, 9);  // P2 runs 5-9
    chart2.add(1, 9, 12); // P1 runs again 9-12 (new block)

    chart2.display();

    // === PART 3: Simulating FCFS Scheduling ===
    cout << "\n=== PART 3: FCFS Scheduling Simulation ===" << endl;

    // Create processes
    Process processes[3] = {
        Process(1, 0, 5, 2),
        Process(2, 1, 3, 1),
        Process(3, 2, 8, 3)};

    // Display initial processes
    cout << "\nProcesses to schedule:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "  ";
      
        cout << endl;
    }

    // Simulate scheduling
    GanttChart chart3;
    simulateFCFS(processes, 3, chart3);

    // Display results
    chart3.display();

    // Display process metrics
    cout << "\n=== PROCESS METRICS ===" << endl;
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse" << endl;
    cout << "---\t-------\t----\t----------\t----------\t-------\t--------" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "P" << processes[i].pid << "\t"
             << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t"
             << processes[i].completionTime << "\t\t"
             << processes[i].turnaroundTime << "\t\t"
             << processes[i].waitingTime << "\t"
             << processes[i].responseTime << endl;
    }

    // === PART 4: Different Scenarios ===
    cout << "\n=== PART 4: Different Scenarios ===" << endl;

    // Scenario 1: Processes arriving at same time
    cout << "\nScenario 1: All arrive at time 0" << endl;
    Process p1[] = {Process(1, 0, 4), Process(2, 0, 6), Process(3, 0, 2)};
    GanttChart g1;

    int time = 0;
    for (int i = 0; i < 3; i++)
    {
        g1.add(p1[i].pid, time, time + p1[i].burstTime);
        time += p1[i].burstTime;
    }
    g1.display();

    // Scenario 2: CPU idle time
    cout << "\nScenario 2: CPU idle (gap between processes)" << endl;
    Process p2[] = {Process(1, 0, 3), Process(2, 10, 4)};
    GanttChart g2;

    int currentTime = 0;
    for (int i = 0; i < 2; i++)
    {
        if (currentTime < p2[i].arrivalTime)
        {
            cout << "CPU idle from " << currentTime << " to " << p2[i].arrivalTime << endl;
            currentTime = p2[i].arrivalTime;
        }
        g2.add(p2[i].pid, currentTime, currentTime + p2[i].burstTime);
        currentTime += p2[i].burstTime;
    }
    g2.display();

    // === PART 5: Calculate Average Metrics ===
    cout << "\n=== PART 5: Average Metrics ===" << endl;

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < 3; i++)
    {
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    cout << "Average Waiting Time: " << totalWT / 3 << endl;
    cout << "Average Turnaround Time: " << totalTAT / 3 << endl;

    cout << "\n========================================" << endl;
    cout << "DAY 2 COMPLETE!" << endl;
    cout << "You have learned:" << endl;
    cout << "  ✓ Gantt Chart structure and display" << endl;
    cout << "  ✓ Merging consecutive same-process blocks" << endl;
    cout << "  ✓ FCFS scheduling simulation" << endl;
    cout << "  ✓ Tracking CPU idle time" << endl;
    cout << "  ✓ Calculating average metrics" << endl;
    cout << "========================================\n"
         << endl;

    return 0;
}