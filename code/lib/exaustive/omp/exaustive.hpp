#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"
#include <bitset>
#include <memory>
#include <vector>

class OpenMp : public Scheduler
{
private:
    int *maxMoviesPerCat_copy;
    int *cnt;
    int *max_cnt;
    int *selectedMovie;

public:
    OpenMp();
    ~OpenMp();
    void generatePermutations();
    void showSelectedMovies();
    void generateOutput();
    void resetVariables();
};