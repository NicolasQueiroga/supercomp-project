#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"

class Thrust : public Scheduler
{
private:
    int *maxMoviesPerCat_copy;
    int *cnt;
    int *max_cnt;
    int *selectedMovie;

public:
    Thrust();
    ~Thrust();
    void generatePermutations();
    void showSelectedMovies();
    void generateOutput();
    void resetVariables();
    bool movieIsValid(const Movie *movie);
};