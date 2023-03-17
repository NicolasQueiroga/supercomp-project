#pragma once

#include "scheduler/scheduler.hpp"
#include "IntervalTree.h"
#include <vector>
#include <map>

class Greedy : public Scheduler
{
private:
    Movie **acceptedMovies;
    int *acceptedMoviesCount;

    std::vector<bool> *agenda;
    std::vector<bool> *movieSchedule;
    std::vector<int> *categoriesCount;

    std::vector<Interval<int, int>> intervals;
    IntervalTree<int, int> intervalTree;

public:
    Greedy();
    ~Greedy();
    void normalSchedule();
    void optimizedSchedule();
    void showAcceptedMovies();
};