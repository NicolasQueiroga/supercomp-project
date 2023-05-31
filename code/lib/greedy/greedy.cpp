#include "greedy.hpp"
#include <chrono>
#include <iostream>

void Greedy::scheduleMovies()
{
    int *i = new int(-1);
    while (++*i < *this->movies)
        if (this->movieIsValid(this->moviesList[*i]))
            this->addMovieToAgenda(this->moviesList[*i]);
    delete i;
}

void Greedy::generateOutput()
{
    this->readMoviesCatalog();
    auto start = std::chrono::high_resolution_clock::now();
    this->scheduleMovies();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << 0 << ' ' << *this->movies << ' ' << *this->categories << ' ' << *this->acceptedMoviesCount << ' ' << elapsed.count() << '\n';
}