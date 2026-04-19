#include "../include/GanttChart.h"

GanttChart::GanttChart()
{
    count = 0;
}

void GanttChart::add(int pid, int start, int end)
{
    if (count > 0 &&
        entries[count - 1].pid == pid &&
        entries[count - 1].endTime == start)
    {
        entries[count - 1].endTime = end;
        cout << " [Merged] p" << pid << " continued from "
             << start << " to " << end;
    }
    else
    {
        entries[count].pid = pid;
        entries[count].startTime = start;
        entries[count].endTime = end;
        count++;
        cout << " [New] p" << pid << " ran from "
             << start << " to " << end << endl;
    }
}

void GanttChart::display()
{
    if (count == 0)
    {
        cout << " No entries to display" << endl;
        return;
    }

    cout << "\n"
         << string(50, '=') << endl;
    cout << "GannttChart " << endl;
    cout << string(50, '=') << endl;

    cout << "  ";
    for (int i = 0; i < count; i++)
    {
        cout << "+---------------";
    }
    cout << "+\n";

    for (int i = 0; i < count; i++)
    {
        cout << "|  P" << entries[i].pid << "    ";
    }
    cout << "|\n";
    for (int i = 0; i < count; i++)
    {
        cout << "+---------------";
    }
    cout << "+\n";

    cout << entries[0].startTime;
    for (int i = 0; i < count; i++)
    {
        cout << "\t" << entries[i].endTime;
    }
    cout << "+\n";

    int totalTime = entries[count - 1].endTime - entries[0].startTime;
    cout << "\nTOtal Time: " << totalTime << "units" << endl;
}
