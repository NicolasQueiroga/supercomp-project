#include "random.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <iostream>

void Random::scheduleMovies()
{
    std::srand(30);

    std::unordered_set<int> *visitedIndexes = new std::unordered_set<int>();
    std::unordered_set<int> *randomChecker = new std::unordered_set<int>();
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
                    break;
                }
                *choosenIndex = std::rand() % *this->movies;
                visitedIndexes->insert(*choosenIndex);
            } while (visitedIndexes->count(*choosenIndex) == 0 && this->agendaBitset->count() > 0);
        }
    }

    delete choosenIndex;
    delete visitedIndexes;
    delete randomChecker;
    delete i;
}