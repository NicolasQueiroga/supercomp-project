#pragma once

#include "scheduler/scheduler.hpp"
#include "IntervalTree.h"
#include <vector>

class Greedy : public Scheduler
{
private:
    std::vector<Interval<int, Movie *>> intervals;
    IntervalTree<int, Movie *> intervalTree;
    Movie **acceptedMovies;

public:
    Greedy();
    ~Greedy();
    void schedule();
    void showAcceptedMovies();
};