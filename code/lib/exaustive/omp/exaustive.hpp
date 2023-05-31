#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"
#include <bitset>
#include <memory>
#include <vector>

class Exaustive : public Scheduler
{
private:
    int *maxMoviesPerPermutation;
    int *maxMovies;
    std::bitset<24> *bestAgendaBitset;

public:
    Exaustive();
    ~Exaustive();
    void generatePermutations();
    void showSelectedMovies();
    void generateOutput();
};