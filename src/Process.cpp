#include "../include/Process.h"
#include <iostream>

Process::Process(int id, int at, int bt,int pr) {
    pid = id;
    arrivalTime = at;
    burstTime = bt;
    priority =pr;

    //execution state
    remainingTime =bt;
    state =NEW;

    //performance metrics
    startTime = 0;
    waitingTime =0;
    turnaroundTime =0;
    completionTime =0;
    responseTime =0;
    firstResponseTime =-1;//-1 means "not yet responded
    
}

void Process::reset(){
    remainingTime = burstTime;
    state =NEW;
    waitingTime =0;
    turnaroundTime =0;
    completionTime =0;
    responseTime =0;
    firstResponseTime =-1;
}

bool Process::isCompleted() const{
    return remainingTime ==0;
}

void Process::display() const{
    cout<< "p"<<pid << "[AT:" << arrivalTime
     <<", BT:" << burstTime; 
     if (priority > 0)
     cout << ", PRI:"<<priority;
     cout << "]";
}