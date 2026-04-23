#ifndef QUEUE_H
#define QUEUE_H

#include "Process.h"

struct Queue
{
    Process **arr;
    int front;
    int rear;
    int capacity;
    int count;

    Queue(int cap = 100);
    ~Queue();
    void enqueue(Process *p);
    Process *dequeue();
    bool isEmpty();
};

#endif