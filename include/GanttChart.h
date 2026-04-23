#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <iostream>
using namespace std;

struct GanttEntry
{
    int pid;
    int startTime;
    int endTime;
};

struct GanttChart
{
    GanttEntry entries[100];
    int count;

    GanttChart();
    void add(int pid, int start, int end);
    void display();
};

#endif