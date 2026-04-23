#include "../include/MinHeap.h"

MinHeap::MinHeap(int cap)
{
    capacity = cap;
    arr = new Process *[capacity];
    size = 0;
}

MinHeap::~MinHeap()
{
    delete[] arr;
}

void MinHeap::heapifyUP(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (arr[index]->remainingTime < arr[parent]->remainingTime)
        {
            Process *temp = arr[index];
            arr[index] = arr[parent];
            arr[parent] = temp;
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2; // FIXED: was 2*index+1

    if (left < size && arr[left]->remainingTime < arr[smallest]->remainingTime)
    {
        smallest = left;
    }
    if (right < size && arr[right]->remainingTime < arr[smallest]->remainingTime)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        Process *temp = arr[index];
        arr[index] = arr[smallest];
        arr[smallest] = temp;
        heapifyDown(smallest);
    }
}

void MinHeap::insert(Process *p)
{
    if (size == capacity)
        return;
    arr[size] = p;
    size++;
    heapifyUP(size - 1);
}

Process *MinHeap::extractMin()
{
    if (size == 0)
        return nullptr;

    Process *min = arr[0];
    arr[0] = arr[size - 1];
    size--;
    heapifyDown(0);
    return min; // FIXED: was missing
}

bool MinHeap::isEmpty()
{
    return size == 0;
}