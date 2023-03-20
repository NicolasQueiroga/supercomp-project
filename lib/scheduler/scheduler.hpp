#pragma once

#include "utils.hpp"

class Scheduler
{
protected:
    int *movies;
    int *categories;
    int **maxMoviesPerCat;
    Movie **moviesList;

public:
    Scheduler();
    ~Scheduler();
    void readMoviesCatalog();
    void showVars();
};