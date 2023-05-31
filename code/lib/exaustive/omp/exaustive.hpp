#pragma once

#include "utils.hpp"
#include "scheduler/scheduler.hpp"
#include <bitset>
#include <memory>
#include <vector>

class Exaustive : public Scheduler
{
private:
    std::vector<Movie> *possibilities;
    int *maxMoviesPerCat_copy;
    int *cnt;

public:
    Exaustive();
    ~Exaustive();
    void generatePermutations();
    void showSelectedMovies();
    void generateOutput();
};