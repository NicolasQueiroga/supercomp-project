#pragma once

#include "scheduler/scheduler.hpp"
#include "IntervalTree.h"
#include <vector>

class Greedy : public Scheduler
{
private:
    std::vector<IntervalTree<int, int>> *intervalTrees;
    Movie **acceptedMovies;

public:
    Greedy();
    ~Greedy();
    void schedule();
    void showAcceptedMovies();
};