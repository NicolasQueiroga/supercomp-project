#include "greedy/greedy.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    Greedy *greedy = new Greedy;
    greedy->readMoviesCatalog();
    // greedy->showVars();
    greedy->schedule();
    greedy->showAcceptedMovies();
    return 0;
}