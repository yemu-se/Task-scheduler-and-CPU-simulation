#ifndef PRIORITY_H
#define PRIORITY_H

#include "Scheduler.h"

struct Priority : Scheduler
{
    bool preemptive;

    Priority(bool preemptiveMode = false);
    void schedule() override;
};
#endif
