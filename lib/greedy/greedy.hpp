#pragma once

#include "scheduler/scheduler.hpp"
#include "IntervalTree.h"
#include <vector>
#include <map>
#include <bitset>

class Greedy : public Scheduler
{
private:
    Movie **acceptedMovies;
    int *acceptedMoviesCount;

    std::bitset<24> *agendaBitset;
    std::bitset<24> *movieScheduleBitset;

    // std::vector<Interval<int, int>> intervals;
    // IntervalTree<int, int> intervalTree;

public:
    Greedy();
    ~Greedy();
    void normalSchedule();
    void optimizedSchedule();
    void showAcceptedMovies();
};