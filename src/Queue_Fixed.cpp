#include "../include/Queue.h"

// Constructor
Queue::Queue(int cap)
{
    capacity = cap;
    arr = new Process *[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor
Queue::~Queue()
{
    delete[] arr;
}

// Add to back
void Queue::enqueue(Process *p)
{
    if (count == capacity)
        return;
    rear = (rear + 1) % capacity;
    arr[rear] = p;
    count++;
}

// Remove from front
Process *Queue::dequeue()
{
    if (isEmpty())
        return nullptr;
        Process *p = arr[front];
    front = (front + 1) % capacity;
    count--;
    return p;
}

// Check if empty
bool Queue::isEmpty()
{
    return count == 0;
}
