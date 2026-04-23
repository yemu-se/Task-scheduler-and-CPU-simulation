#include <iostream>
#include "include/Process.h"
#include "include/MinHeap.h"

using namespace std;

int main() {
    cout << "=== PROGRAM STARTED ===" << endl;
    
    MinHeap heap(10);
    cout << "Heap created" << endl;
    
    Process p1(1, 0, 8, 2);
    Process p2(2, 0, 3, 1);
    Process p3(3, 0, 5, 3);
    Process p4(4, 0, 1, 2);
    
    p1.remainingTime = 8;
    p2.remainingTime = 3;
    p3.remainingTime = 5;
    p4.remainingTime = 1;
    
    cout << "Inserting P1" << endl;
    heap.insert(&p1);
    cout << "Inserting P2" << endl;
    heap.insert(&p2);
    cout << "Inserting P3" << endl;
    heap.insert(&p3);
    cout << "Inserting P4" << endl;
    heap.insert(&p4);
    
    cout << "Extracting: ";
    while (!heap.isEmpty()) {
        Process* p = heap.extractMin();
        cout << "P" << p->pid << "(" << p->remainingTime << ") ";
    }
    cout << endl;
    
    cout << "=== PROGRAM FINISHED ===" << endl;
    return 0;
}