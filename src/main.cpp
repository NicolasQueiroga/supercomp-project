#include "greedy/greedy.hpp"
#include "random/random.hpp"
#include <chrono>
#include <iostream>

int main(int argc, char **argv)
{
    if (argv[1][0] == '1')
    {
        Random random = Random();
        random.readMoviesCatalog();

        // start timer here
        auto start = std::chrono::high_resolution_clock::now();
        random.scheduleMovies();
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << 0 << ' ' << *random.movies << ' ' << *random.categories << ' ' << *random.acceptedMoviesCount << ' ' << elapsed.count() << '\n';

        // random.showAcceptedMovies();
    }
    else if (argv[1][0] == '0')
    {
        Greedy greedy = Greedy();
        greedy.readMoviesCatalog();

        // start timer here
        auto start = std::chrono::high_resolution_clock::now();
        greedy.scheduleMovies();
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << 0 << ' ' << *greedy.movies << ' ' << *greedy.categories << ' ' << *greedy.acceptedMoviesCount << ' ' << elapsed.count() << '\n';
        // greedy.showAcceptedMovies();
    }
    return 0;
}