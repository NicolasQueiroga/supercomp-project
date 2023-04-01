#pragma once

#include "utils.hpp"
#include <bitset>
#include <memory>

class Scheduler
{
protected:
    int *maxMoviesPerCat;
    Movie **moviesList;

    Movie **acceptedMovies;
    std::bitset<24> *agendaBitset;
    std::bitset<24> *movieScheduleBitset;

public:
    int *movies;
    int *categories;
    int *acceptedMoviesCount;
    Scheduler();
    ~Scheduler();
    void readMoviesCatalog();
    void showVars();
    bool movieIsValid(Movie *movie);
    void addMovieToAgenda(Movie *movie);
    void showAcceptedMovies();
};