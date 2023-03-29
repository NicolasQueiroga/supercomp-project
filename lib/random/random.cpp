#include "random.hpp"
#include <algorithm>
#include <unordered_set>
#include <vector>

void Random::scheduleMovies()
{
    std::vector<int> *randomMoviesIndexes = new std::vector<int>();
    int *randomIndex = new int;
    std::unordered_set<int> *visitedIndexes = new std::unordered_set<int>();
    int *i = new int;

    for (*i = -1; *i < *this->movies; ++*i)
    {
        if (std::find(randomMoviesIndexes->begin(), randomMoviesIndexes->end(), *i) == randomMoviesIndexes->end())
        {
            if (std::rand() % 100 < 75 && this->movieIsValid(this->moviesList[*i]))
                this->addMovieToAgenda(this->moviesList[*i]);
            else
            {
                do
                {
                    if (this->movieIsValid(this->moviesList[*randomIndex]))
                    {
                        this->addMovieToAgenda(this->moviesList[*randomIndex]);
                        break;
                    }
                    *randomIndex = std::rand() % *this->movies;
                    visitedIndexes->insert(*randomIndex);
                } while (visitedIndexes->count(*randomIndex) == 0 && this->agendaBitset->count() > 0);
            }
        }
    }

    delete randomIndex;
    delete randomMoviesIndexes;
    delete visitedIndexes;
    delete i;
}