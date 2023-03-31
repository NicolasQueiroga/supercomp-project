#pragma once

#include "scheduler/scheduler.hpp"
#include "greedy/greedy.hpp"

class Random : public Scheduler
{
public:
    void scheduleMovies();
};