#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"
#include <thrust/device_vector.h>

class Thrust : public Scheduler
{
private:


public:
    Thrust();
    ~Thrust();
    void generatePermutations();
    void showSelectedMovies();
    void generateOutput();
    void logic();
    bool movieIsValid(const Movie *movie);
};