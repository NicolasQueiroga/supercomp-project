#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"

class Thrust : public Scheduler
{
private:
public:
    struct MovieCount;
    Thrust();
    ~Thrust();
    void scheduleMovies();
    void generateOutput();
};