#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Process.h"
struct Node{
Process* data;
Node* next;

Node(Process* p): data(p),next(nullptr){}
};

class LinkedList{
private:
Node* head;
int size;
public:
LinkedList();

~LinkedList();

void inser(Process* p);//


Process* getHead();//

int getSize();
bool isEmpty();

void clear();

void sortByArrivalTime();//


};
#endif