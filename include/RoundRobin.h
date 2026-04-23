#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H
#include "Scheduler.h"
#include "Queue.h"
struct RoundRobin : Scheduler
{
    int timeQuantum;

    RoundRobin(int tq);
    void schedule() override;
};
#endif
