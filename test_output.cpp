#include "include/Process.h" 
#include "include/MinHeap.h" 
using namespace std; 
int main() { 
    ofstream file("output.txt"); 
    MinHeap heap(10); 
    Process p1(1,0,8,2); 
    Process p2(2,0,3,1); 
    Process p3(3,0,5,3); 
    Process p4(4,0,1,2); 
    p1.remainingTime=8; p2.remainingTime=3; p3.remainingTime=5; p4.remainingTime=1; 
    while(!heap.isEmpty()) { 
        Process* p = heap.extractMin(); 
    } 
    file.close(); 
    return 0; 
} 
