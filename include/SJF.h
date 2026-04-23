#ifndef SJF_H
#define SJF_H

#include "Scheduler.h"
#include "MinHeap.h"

struct SJF : Scheduler {
    void schedule() override;
};

#endif