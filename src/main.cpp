#include "greedy/greedy.hpp"
#include "random/random.hpp"

// #define RANDOM

int main(int argc, char **argv)
{
#ifndef RANDOM
    Greedy greedy = Greedy();
    greedy.readMoviesCatalog();
    greedy.scheduleMovies();
    greedy.showAcceptedMovies();
#else
    Random random = Random();
    random.readMoviesCatalog();
    random.scheduleMovies();
    random.showAcceptedMovies();
#endif
    return 0;
}