#ifndef GANTTCHART_H
#define GANTTCHART_H

#include <iostream>
using namespace std;
struct GanttEntry // represents one block in the Gantt chart.
{
    int pid;
    int startTime;
    int endTime;
};
class GanttChart
{
private:
    GanttEntry entries[100];
    int count;

public:
    GanttChart();

    // If same process runs continuously, merge with previous
    void add(int pid, int start, int end);

    void display();

    int getCount();

    GanttEntry getLast();

    void clear();
};

#endif
