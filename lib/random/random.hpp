#pragma once

// #define SEED 42

#include <cstdlib>
#include <ctime>
#include "scheduler/scheduler.hpp"
#include "greedy/greedy.hpp"

#ifdef SEED
#define RANDOM_SEED std::srand(SEED);
#else
#define RANDOM_SEED std::srand(std::time(nullptr));
#endif

class Random : public Scheduler
{
public:
    void scheduleMovies();
};