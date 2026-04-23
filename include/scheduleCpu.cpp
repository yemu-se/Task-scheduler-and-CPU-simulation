#include <iostream>
#include <iomanip>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// ENUMS AND PROCESS STRUCTURE
// ============================================================

enum ProcessState { NEW, READY, RUNNING, TERMINATED };

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    ProcessState state;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int responseTime;
    int firstResponseTime;
    Process* next;
    
    Process(int id = 0, int at = 0, int bt = 0, int pr = 0) {
        pid = id;
        arrivalTime = at;
        burstTime = bt;
        priority = pr;
        remainingTime = bt;
        state = NEW;
        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
        responseTime = 0;
        firstResponseTime = -1;
        next = nullptr;
    }
    
    void reset() {
        remainingTime = burstTime;
        state = NEW;
        waitingTime = 0;
        turnaroundTime = 0;
        completionTime = 0;
        responseTime = 0;
        firstResponseTime = -1;
    }
    
    bool isCompleted() const {
        return remainingTime == 0;
    }
    
    void display() const {
        cout << "P" << pid << " [AT:" << arrivalTime << ", BT:" << burstTime;
        if (priority > 0) cout << ", PRI:" << priority;
        cout << "]";
    }
};

// ============================================================
// GANTT CHART
// ============================================================

struct GanttEntry {
    int pid;
    int startTime;
    int endTime;
};

struct GanttChart {
    GanttEntry entries[100];
    int count;
    
    GanttChart() {
        count = 0;
    }
    
    void add(int pid, int start, int end) {
        if (count > 0 && entries[count - 1].pid == pid && entries[count - 1].endTime == start) {
            entries[count - 1].endTime = end;
        } else if (count < 100) {
            entries[count].pid = pid;
            entries[count].startTime = start;
            entries[count].endTime = end;
            count++;
        }
    }
    
    void display() {
        if (count == 0) return;
        
        cout << "\nGantt Chart:\n";
        cout << " ";
        for (int i = 0; i < count; i++) cout << "+----------";
        cout << "+\n ";
        for (int i = 0; i < count; i++) cout << "|   P" << entries[i].pid << "    ";
        cout << "|\n ";
        for (int i = 0; i < count; i++) cout << "+----------";
        cout << "+\n";
        cout << entries[0].startTime;
        for (int i = 0; i < count; i++) cout << "\t" << entries[i].endTime;
        cout << "\n";
    }
    
    int getCount() { return count; }
    
    GanttEntry getLast() {
        if (count > 0) return entries[count - 1];
        GanttEntry empty = {0, 0, 0};
        return empty;
    }
    
    void clear() { count = 0; }
};

// ============================================================
// LINKED LIST
// ============================================================

struct Node {
    Process* data;
    Node* next;
    Node(Process* p) : data(p), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    int size;
    
    LinkedList() {
        head = nullptr;
        size = 0;
    }
    
    ~LinkedList() {
        clear();
    }
    
    void insert(Process* p) {
        Node* newNode = new Node(p);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }
    
    Process* remove(int pid) {
        if (head == nullptr) return nullptr;
        
        if (head->data->pid == pid) {
            Node* temp = head;
            head = head->next;
            Process* removedProcess = temp->data;
            delete temp;
            size--;
            return removedProcess;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data->pid != pid) {
            current = current->next;
        }
        
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            Process* removedProcess = temp->data;
            delete temp;
            size--;
            return removedProcess;
        }
        
        return nullptr;
    }
    
    Process* getHead() {
        if (head == nullptr) return nullptr;
        return head->data;
    }
    
    int getSize() {
        return size;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }
    
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }
    
    void sortByArrivalTime() {
        if (size <= 1) return;
        
        for (int i = 0; i < size - 1; i++) {
            Node* current = head;
            for (int j = 0; j < size - i - 1; j++) {
                Node* next = current->next;
                if (current->data->arrivalTime > next->data->arrivalTime) {
                    Process* temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                }
                current = next;
            }
        }
    }
    
    void display() {
        if (head == nullptr) return;
        
        Node* temp = head;
        while (temp != nullptr) {
            cout << "P" << temp->data->pid;
            if (temp->next != nullptr) cout << " → ";
            temp = temp->next;
        }
        cout << " → NULL" << endl;
    }
};

// ============================================================
// QUEUE
// ============================================================

struct Queue {
    Process** arr;
    int front;
    int rear;
    int capacity;
    int count;
    
    Queue(int cap = 100) {
        capacity = cap;
        arr = new Process*[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }
    
    ~Queue() {
        delete[] arr;
    }
    
    void enqueue(Process* p) {
        if (count == capacity) return;
        rear = (rear + 1) % capacity;
        arr[rear] = p;
        count++;
    }
    
    Process* dequeue() {
        if (isEmpty()) return nullptr;
        Process* p = arr[front];
        front = (front + 1) % capacity;
        count--;
        return p;
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    int getSize() {
        return count;
    }
    
    void clear() {
        front = 0;
        rear = -1;
        count = 0;
    }
};

// ============================================================
// MIN HEAP
// ============================================================

struct MinHeap {
    Process** arr;
    int capacity;
    int size;
    
    MinHeap(int cap = 100) {
        capacity = cap;
        arr = new Process*[capacity];
        size = 0;
    }
    
    ~MinHeap() {
        delete[] arr;
    }
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (arr[index]->remainingTime < arr[parent]->remainingTime) {
                Process* temp = arr[index];
                arr[index] = arr[parent];
                arr[parent] = temp;
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < size && arr[left]->remainingTime < arr[smallest]->remainingTime)
            smallest = left;
        if (right < size && arr[right]->remainingTime < arr[smallest]->remainingTime)
            smallest = right;
        
        if (smallest != index) {
            Process* temp = arr[index];
            arr[index] = arr[smallest];
            arr[smallest] = temp;
            heapifyDown(smallest);
        }
    }
    
    void insert(Process* p) {
        if (size == capacity) return;
        arr[size] = p;
        size++;
        heapifyUp(size - 1);
    }
    
    Process* extractMin() {
        if (size == 0) return nullptr;
        Process* min = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    int getSize() {
        return size;
    }
    
    void clear() {
        size = 0;
    }
};

// ============================================================
// CPU CLASS
// ============================================================

struct CPU {
    int currentTime;
    Process* runningProcess;
    
    CPU() {
        currentTime = 0;
        runningProcess = nullptr;
    }
    
    int getCurrentTime() {
        return currentTime;
    }
    
    bool isIdle() {
        return runningProcess == nullptr;
    }
    
    void loadProcess(Process* p, int startTime) {
        if (startTime > currentTime) {
            currentTime = startTime;
        }
        runningProcess = p;
        p->state = RUNNING;
        
        if (p->firstResponseTime == -1) {
            p->firstResponseTime = currentTime;
            p->responseTime = p->firstResponseTime - p->arrivalTime;
        }
    }
    
    void unloadProcess() {
        if (runningProcess) {
            runningProcess->completionTime = currentTime;
            runningProcess->turnaroundTime = runningProcess->completionTime - runningProcess->arrivalTime;
            runningProcess->waitingTime = runningProcess->turnaroundTime - runningProcess->burstTime;
            runningProcess->state = TERMINATED;
            runningProcess = nullptr;
        }
    }
    
    void preempt() {
        if (runningProcess) {
            runningProcess->state = READY;
            runningProcess = nullptr;
        }
    }
    
    int execute(int timeQuantum = -1) {
        if (!runningProcess) return 0;
        
        int executeTime;
        if (timeQuantum == -1) {
            executeTime = runningProcess->remainingTime;
        } else {
            executeTime = min(timeQuantum, runningProcess->remainingTime);
        }
        
        runningProcess->remainingTime -= executeTime;
        currentTime += executeTime;
        
        return executeTime;
    }
};

// ============================================================
// SCHEDULER BASE CLASS
// ============================================================

struct Scheduler {
    LinkedList* processList;
    CPU cpu;
    GanttChart gantt;
    float totalWaitingTime;
    float totalTurnaroundTime;
    float totalResponseTime;
    
    Scheduler() {
        processList = new LinkedList();
        totalWaitingTime = 0;
        totalTurnaroundTime = 0;
        totalResponseTime = 0;
    }
    
    ~Scheduler() {
        delete processList;
    }
    
    void addProcess(int pid, int at, int bt, int pr = 0) {
        Process* p = new Process(pid, at, bt, pr);
        processList->insert(p);
    }
    
    void displayResults() {
        gantt.display();
        
        cout << "\n" << string(120, '-') << endl;
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
        
        Process* temp = processList->getHead();
        int n = 0;
        totalWaitingTime = 0;
        totalTurnaroundTime = 0;
        totalResponseTime = 0;
        
        while (temp != nullptr) {
            cout << left << setw(10) << ("P" + to_string(temp->pid))
                 << setw(15) << temp->arrivalTime
                 << setw(15) << temp->burstTime
                 << setw(20) << temp->completionTime
                 << setw(20) << temp->turnaroundTime
                 << setw(15) << temp->waitingTime
                 << setw(15) << temp->responseTime << endl;
            
            totalWaitingTime += temp->waitingTime;
            totalTurnaroundTime += temp->turnaroundTime;
            totalResponseTime += temp->responseTime;
            n++;
            temp = temp->next;
        }
        cout << string(120, '-') << endl;
        
        if (n > 0) {
            cout << fixed << setprecision(2);
            cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
            cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;
            cout << "Average Response Time: " << totalResponseTime / n << endl;
        }
    }
    
    virtual void schedule() = 0;
};

// ============================================================
// FCFS SCHEDULER
// ============================================================

struct FCFS : Scheduler {
    void schedule() override {
        cout << "\n=== FCFS SCHEDULING ===\n";
        
        processList->sortByArrivalTime();
        
        int currentTime = 0;
        Process* temp = processList->getHead();
        
        while (temp != nullptr) {
            if (currentTime < temp->arrivalTime) {
                currentTime = temp->arrivalTime;
            }
            
            cpu.loadProcess(temp, currentTime);
            gantt.add(temp->pid, currentTime, currentTime + temp->burstTime);
            cpu.execute();
            currentTime = cpu.getCurrentTime();
            cpu.unloadProcess();
            
            temp = temp->next;
        }
        
        displayResults();
    }
};

// ============================================================
// SJF SCHEDULER
// ============================================================

struct SJF : Scheduler {
    void schedule() override {
        cout << "\n=== SJF SCHEDULING (Non-Preemptive) ===\n";
        
        Process* processes[100];
        int processCount = 0;
        Process* temp = processList->getHead();
        
        while (temp != nullptr) {
            processes[processCount++] = temp;
            temp = temp->next;
        }
        
        for (int i = 0; i < processCount - 1; i++) {
            for (int j = 0; j < processCount - i - 1; j++) {
                if (processes[j]->arrivalTime > processes[j + 1]->arrivalTime) {
                    swap(processes[j], processes[j + 1]);
                }
            }
        }
        
        for (int i = 0; i < processCount; i++) {
            processes[i]->remainingTime = processes[i]->burstTime;
        }
        
        MinHeap readyQueue;
        int currentTime = 0;
        int completed = 0;
        int index = 0;
        
        while (completed < processCount) {
            while (index < processCount && processes[index]->arrivalTime <= currentTime) {
                readyQueue.insert(processes[index]);
                index++;
            }
            
            if (!readyQueue.isEmpty()) {
                Process* shortest = readyQueue.extractMin();
                
                if (currentTime < shortest->arrivalTime) {
                    currentTime = shortest->arrivalTime;
                }
                
                cpu.loadProcess(shortest, currentTime);
                gantt.add(shortest->pid, currentTime, currentTime + shortest->remainingTime);
                cpu.execute();
                currentTime = cpu.getCurrentTime();
                cpu.unloadProcess();
                completed++;
            } else if (index < processCount) {
                currentTime = processes[index]->arrivalTime;
            }
        }
        
        displayResults();
    }
};

// ============================================================
// ROUND ROBIN SCHEDULER
// ============================================================

struct RoundRobin : Scheduler {
    int timeQuantum;
    
    RoundRobin(int tq = 4) : timeQuantum(tq) {}
    
    void schedule() override {
        cout << "\n=== ROUND ROBIN SCHEDULING (Quantum = " << timeQuantum << ") ===\n";
        
        Process* processes[100];
        int processCount = 0;
        Process* temp = processList->getHead();
        
        while (temp != nullptr) {
            processes[processCount++] = temp;
            temp = temp->next;
        }
        
        for (int i = 0; i < processCount - 1; i++) {
            for (int j = 0; j < processCount - i - 1; j++) {
                if (processes[j]->arrivalTime > processes[j + 1]->arrivalTime) {
                    swap(processes[j], processes[j + 1]);
                }
            }
        }
        
        for (int i = 0; i < processCount; i++) {
            processes[i]->remainingTime = processes[i]->burstTime;
        }
        
        Queue readyQueue;
        int currentTime = 0;
        int completed = 0;
        int index = 0;
        
        while (completed < processCount) {
            while (index < processCount && processes[index]->arrivalTime <= currentTime) {
                readyQueue.enqueue(processes[index]);
                index++;
            }
            
            if (!readyQueue.isEmpty()) {
                Process* current = readyQueue.dequeue();
                
                int executeTime = (timeQuantum < current->remainingTime) ? timeQuantum : current->remainingTime;
                int startTime = currentTime;
                
                cpu.loadProcess(current, startTime);
                cpu.execute(executeTime);
                currentTime = cpu.getCurrentTime();
                current->remainingTime -= executeTime;
                
                gantt.add(current->pid, startTime, currentTime);
                
                if (current->remainingTime == 0) {
                    cpu.unloadProcess();
                    completed++;
                } else {
                    cpu.unloadProcess();
                    
                    while (index < processCount && processes[index]->arrivalTime <= currentTime) {
                        readyQueue.enqueue(processes[index]);
                        index++;
                    }
                    
                    readyQueue.enqueue(current);
                }
            } else if (index < processCount) {
                currentTime = processes[index]->arrivalTime;
            }
        }
        
        displayResults();
    }
};

// ============================================================
// PRIORITY SCHEDULER
// ============================================================

struct Priority : Scheduler {
    bool preemptive;
    
    Priority(bool preemptiveMode = false) : preemptive(preemptiveMode) {}
    
    void schedule() override {
        cout << "\n=== PRIORITY SCHEDULING (" << (preemptive ? "Preemptive" : "Non-Preemptive") << ") ===\n";
        
        Process* processes[100];
        int processCount = 0;
        Process* temp = processList->getHead();
        
        while (temp != nullptr) {
            processes[processCount++] = temp;
            temp = temp->next;
        }
        
        for (int i = 0; i < processCount - 1; i++) {
            for (int j = 0; j < processCount - i - 1; j++) {
                if (processes[j]->arrivalTime > processes[j + 1]->arrivalTime) {
                    swap(processes[j], processes[j + 1]);
                }
            }
        }
        
        for (int i = 0; i < processCount; i++) {
            processes[i]->remainingTime = processes[i]->burstTime;
        }
        
        Process* readyQueue[100];
        int readyCount = 0;
        int currentTime = 0;
        int completed = 0;
        int index = 0;
        Process* runningProcess = nullptr;
        
        while (completed < processCount) {
            while (index < processCount && processes[index]->arrivalTime <= currentTime) {
                readyQueue[readyCount++] = processes[index];
                index++;
            }
            
            if (preemptive && runningProcess != nullptr && readyCount > 0) {
                int highestPriorityIndex = 0;
                for (int i = 1; i < readyCount; i++) {
                    if (readyQueue[i]->priority < readyQueue[highestPriorityIndex]->priority) {
                        highestPriorityIndex = i;
                    }
                }
                if (readyQueue[highestPriorityIndex]->priority < runningProcess->priority) {
                    cpu.preempt();
                    readyQueue[readyCount++] = runningProcess;
                    runningProcess = nullptr;
                }
            }
            
            if (runningProcess == nullptr && readyCount > 0) {
                int highestPriorityIndex = 0;
                for (int i = 1; i < readyCount; i++) {
                    if (readyQueue[i]->priority < readyQueue[highestPriorityIndex]->priority) {
                        highestPriorityIndex = i;
                    }
                }
                
                runningProcess = readyQueue[highestPriorityIndex];
                
                for (int i = highestPriorityIndex; i < readyCount - 1; i++) {
                    readyQueue[i] = readyQueue[i + 1];
                }
                readyCount--;
                
                int startTime = currentTime;
                cpu.loadProcess(runningProcess, startTime);
                gantt.add(runningProcess->pid, startTime, startTime + runningProcess->remainingTime);
                cpu.execute();
                currentTime = cpu.getCurrentTime();
                
                if (runningProcess->remainingTime == 0) {
                    cpu.unloadProcess();
                    completed++;
                    runningProcess = nullptr;
                }
            } else if (index < processCount) {
                currentTime = processes[index]->arrivalTime;
            }
        }
        
        displayResults();
    }
};

// ============================================================
// MAIN FUNCTION WITH MENU
// ============================================================

void displayMenu() {
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

void inputProcesses(Scheduler* scheduler) {
    int n;
    cout << "\nEnter number of processes: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int at, bt, pr;
        cout << "\nProcess P" << i + 1 << ":" << endl;
        cout << "  Arrival Time: ";
        cin >> at;
        cout << "  Burst Time: ";
        cin >> bt;
        cout << "  Priority (1 = highest): ";
        cin >> pr;
        
        scheduler->addProcess(i + 1, at, bt, pr);
    }
}

void runFCFS() {
    FCFS scheduler;
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runSJF() {
    SJF scheduler;
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runRoundRobin() {
    int quantum;
    cout << "\nEnter Time Quantum: ";
    cin >> quantum;
    
    RoundRobin scheduler(quantum);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runPriorityNonPreemptive() {
    Priority scheduler(false);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

void runPriorityPreemptive() {
    Priority scheduler(true);
    inputProcesses(&scheduler);
    scheduler.schedule();
}

int main() {
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
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
        
        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while (choice != 6);
    
    return 0;
}