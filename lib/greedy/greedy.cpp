#include "greedy.hpp"
#include <algorithm>
#include <map>

Greedy::Greedy()
{
}

Greedy::~Greedy()
{
}

void Greedy::schedule()
{
    std::map<int, int> *categoriesMap = new std::map<int, int>;
    for (int i = 0; i < *(this->categories); i++)
        categoriesMap->insert(std::pair<int, int>(i, 0));

    this->acceptedMovies = new Movie *[24];

    std::sort(this->moviesList, this->moviesList + *(this->movies), [](Movie *a, Movie *b)
              { return a->endTime < b->endTime; });

    int i = -1, j;
    bool overlaps;
    while (++i < *(this->movies))
    {
        if (this->moviesList[i]->startTime < this->moviesList[i]->endTime && categoriesMap->at(this->moviesList[i]->category) < *(this->maxMoviesPerCat[this->moviesList[i]->category]))
        {
            // check if movie overlaps with any other accepted movie
            overlaps = false;
            j = -1;
            while (++j < i)
            {
                if (this->moviesList[i]->startTime < this->moviesList[j]->endTime && this->moviesList[j]->startTime < this->moviesList[i]->endTime)
                {
                    overlaps = true;
                    break;
                }
            }
            if (!overlaps)
            {
                this->acceptedMovies[i] = this->moviesList[i];
                categoriesMap->at(this->moviesList[i]->category)++;
            }
        }
    }
}

void Greedy::showAcceptedMovies()
{
    int i = -1;
    while (this->acceptedMovies[++i] != nullptr)
        std::cout << this->acceptedMovies[i]->category << ' ' << this->acceptedMovies[i]->startTime << ' ' << this->acceptedMovies[i]->endTime << '\n';
}