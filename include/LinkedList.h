#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Process.h"

struct Node
{
    Process *data;
    Node *next;
    Node(Process *p) : data(p), next(nullptr) {}
};

struct LinkedList
{
    Node *head;
    int size;

    LinkedList();
    ~LinkedList();
    void insert(Process *p);
    Node *getHead();
    void clear();
    void sortByArrivalTime();
};

#endif