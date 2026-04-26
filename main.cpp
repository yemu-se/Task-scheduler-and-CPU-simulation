#include <iostream>
#include <limits>
#include "include/FCFS.h"
#include "include/SJF.h"
#include "include/RoundRobin.h"
#include "include/Priority.h"

using namespace std;

bool readInt(const char *prompt, int &value, int minValue, int maxValue)
{
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (cin.fail())
        {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minValue || value > maxValue)
        {
            cout << "Value must be between " << minValue << " and " << maxValue << ".\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }
}

void displayMenu()
{
    cout << "\n========================================" << endl;
    cout << "     CPU SCHEDULING SIMULATOR" << endl;
    cout << "========================================" << endl;
    cout << "  1. FCFS (First Come First Served)" << endl;
    cout << "  2. SJF (Shortest Job First)" << endl;
    cout << "  3. Round Robin" << endl;
    cout << "  4. Priority (Non-Preemptive)" << endl;
    cout << "  5. Priority (Preemptive)" << endl;
    cout << "  6. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void inputProcesses(Scheduler *scheduler)
{
    int n;
    readInt("\nEnter number of processes: ", n, 1, 100);

    for (int i = 0; i < n; i++)
    {
        int at, bt, pr;
        cout << "\nProcess P" << i + 1 << ":" << endl;
        readInt("  Arrival Time: ", at, 0, 10000);
        readInt("  Burst Time: ", bt, 1, 10000);
        readInt("  Priority (1 = highest): ", pr, 1, 1000);

        scheduler->addProcess(i + 1, at, bt, pr);
    }
}

void runFCFS()
{
    FCFS scheduler;
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runSJF()
{
    SJF scheduler;
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runRoundRobin()
{
    int quantum;
    cout << "\nEnter Time Quantum: ";
    cin >> quantum;

    RoundRobin scheduler(quantum);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runPriorityNonPreemptive()
{
    Priority scheduler(false);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runPriorityPreemptive()
{
    Priority scheduler(true);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

int main()
{
    int choice;

    do
    {
        displayMenu();
        readInt("", choice, 1, 6);

        switch (choice)
        {
        case 1:
            runFCFS();
            break;
        case 2:
            runSJF();
            break;
        case 3:
            runRoundRobin();
            break;
        case 4:
            runPriorityNonPreemptive();
            break;
        case 5:
            runPriorityPreemptive();
            break;
        case 6:
            cout << "\nExiting program. Goodbye!" << endl;
            break;
        default:
            cout << "\nInvalid choice! Please enter 1-6." << endl;
        }

        if (choice != 6)
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 6);

    return 0;
}