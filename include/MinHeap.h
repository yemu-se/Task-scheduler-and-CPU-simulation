#ifndef MINHEAP_H
#define MINHEAP_H

#include "Process.h"

struct MinHeap
{
    Process **arr;
    int capacity;
    int size;

    MinHeap(int cap = 100);
    ~MinHeap();
    void insert(Process *p);
    Process *extractMin();
    bool isEmpty();

    void heapifyUP(int index);
    void heapifyDown(int index);
};

#endif