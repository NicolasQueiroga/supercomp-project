#include "greedy/greedy.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    std::unique_ptr<Greedy> greedy = std::make_unique<Greedy>();
    greedy->readMoviesCatalog();
    greedy->normalSchedule();
    greedy->showAcceptedMovies();
    return 0;
}