#include "random.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <chrono>


void Random::scheduleMovies()
{
    std::srand(std::time(nullptr));

    std::unordered_set<int> *visitedIndexes = new std::unordered_set<int>();
    int *i = new int(-1);
    int *choosenIndex = new int;

    while (++*i < *this->movies && this->agendaBitset->count() < 24)
    {
        if (std::rand() % 100 < 75)
        {
            if (this->movieIsValid(this->moviesList[*i]) && visitedIndexes->count(*i) == 0)
            {
                this->addMovieToAgenda(this->moviesList[*i]);
                visitedIndexes->insert(*i);
            }
        }
        else
        {
            *choosenIndex = std::rand() % *this->movies;
            do
            {
                if (this->movieIsValid(this->moviesList[*choosenIndex]))
                {
                    this->addMovieToAgenda(this->moviesList[*choosenIndex]);
                    visitedIndexes->insert(*choosenIndex);
                    break;
                }
                *choosenIndex = std::rand() % *this->movies;
                visitedIndexes->insert(*choosenIndex);
            } while (visitedIndexes->count(*choosenIndex) == 0 && this->agendaBitset->count() > 0);
        }
    }

    delete choosenIndex;
    delete visitedIndexes;
    delete i;
}

void Random::generateOutput()
{
    this->readMoviesCatalog();
    auto start = std::chrono::high_resolution_clock::now();
    this->scheduleMovies();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << 1 << ' ' << *this->movies << ' ' << *this->categories << ' ' << *this->acceptedMoviesCount << ' ' << elapsed.count() << '\n';
}