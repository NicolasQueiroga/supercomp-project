#pragma once

#include "utils.hpp"
#include <bitset>
#include <memory>

class Scheduler
{
protected:
    int *movies;
    int *categories;
    int *maxMoviesPerCat;
    Movie **moviesList;

    Movie **acceptedMovies;
    int *acceptedMoviesCount;
    std::bitset<24> *agendaBitset;
    std::bitset<24> *movieScheduleBitset;

public:
    Scheduler();
    ~Scheduler();
    void readMoviesCatalog();
    void showVars();
    bool movieIsValid(Movie *movie);
    void addMovieToAgenda(Movie *movie);
    void showAcceptedMovies();
};