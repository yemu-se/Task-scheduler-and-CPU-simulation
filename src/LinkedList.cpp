
#include "../include/LinkedList.h"
#include <iostream>
using namespace std;
LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::insert(Process *p)
{
    Node *newNode = new Node(p);

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    size++;
}

Node *LinkedList::getHead()
{
    return head;
}

void LinkedList::clear()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *temp = current;
        current = current->next;
        delete temp->data;
        delete temp;
    }
    head = nullptr;
    size = 0;
}

void LinkedList::sortByArrivalTime()
{
    if (size <= 1)
        return;
    for (int i = 0; i < size - 1; i++)
    {
        Node *current = head;
        for (int j = 0; j < size - i - 1; j++)
        {
            Node *next = current->next;
            if (current->data->arrivalTime > next->data->arrivalTime)
            {
                swap(current->data, next->data);
            }
            current = next;
        }
    }
}
