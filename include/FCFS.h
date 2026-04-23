#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

struct FCFS : Scheduler
{
    void schedule() override;
};

#endif