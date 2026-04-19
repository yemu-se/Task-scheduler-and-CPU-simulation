#ifndef QUEUE_H
#define QUEUE_H

#include "Process.h"

class Queue {
private:
    Process** arr;
    int front;
    int rear;
    int capacity;
    int count;
    public:
        Queue(int cap = 100);
    ~Queue();
    void enqueue(Process* p);
    Process* dequeue();
    bool isEmpty();
};
#endif
