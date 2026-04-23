#include <iostream>
using namespace std;

// Process structure
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    Process* next;
    
    Process(int id = 0, int at = 0, int bt = 0, int pr = 0) {
        pid = id;
        arrivalTime = at;
        burstTime = bt;
        priority = pr;
        remainingTime = bt;
        next = nullptr;
    }
};

// MinHeap class
class MinHeap {
private:
    Process** arr;
    int capacity;
    int size;
    
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
    
public:
    MinHeap(int cap = 100) {
        capacity = cap;
        arr = new Process*[capacity];
        size = 0;
    }
    
    ~MinHeap() { delete[] arr; }
    
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
    
    bool isEmpty() { return size == 0; }
};

int main() {
    cout << "\n========================================" << endl;
    cout << "DAY 5: MIN HEAP TEST (SJF Ready Queue)" << endl;
    cout << "========================================\n" << endl;
    
    MinHeap heap(10);
    
    Process p1(1, 0, 8, 2);
    Process p2(2, 0, 3, 1);
    Process p3(3, 0, 5, 3);
    Process p4(4, 0, 1, 2);
    
    p1.remainingTime = 8;
    p2.remainingTime = 3;
    p3.remainingTime = 5;
    p4.remainingTime = 1;
    
    cout << "Inserting: P1(BT=8), P2(BT=3), P3(BT=5), P4(BT=1)\n" << endl;
    
    heap.insert(&p1);
    cout << "  Inserted P1 (BT=8)" << endl;
    heap.insert(&p2);
    cout << "  Inserted P2 (BT=3)" << endl;
    heap.insert(&p3);
    cout << "  Inserted P3 (BT=5)" << endl;
    heap.insert(&p4);
    cout << "  Inserted P4 (BT=1)" << endl;
    
    cout << "\nExtracting (SJF order): ";
    while (!heap.isEmpty()) {
        Process* p = heap.extractMin();
        cout << "P" << p->pid << "(" << p->remainingTime << ") ";
    }
    cout << endl;
    
    cout << "\n========================================" << endl;
    cout << "DAY 5 COMPLETE!" << endl;
    cout << "========================================\n" << endl;
    
    // THIS PAUSES THE WINDOW SO YOU CAN SEE THE OUTPUT
    cout << "Press Enter to exit...";
    cin.get();
    
    return 0;
}