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

    int i = -1;
    while (this->moviesList[++i] != nullptr)
    {
        if (categoriesMap->at(this->moviesList[i]->category) == 0)
        {
            this->acceptedMovies[i] = this->moviesList[i];
            categoriesMap->at(this->moviesList[i]->category) = 1;
        }
        else
        {
            int j = -1;
            while (this->acceptedMovies[++j] != nullptr)
                if (this->acceptedMovies[j]->category == this->moviesList[i]->category)
                    if (this->acceptedMovies[j]->endTime <= this->moviesList[i]->startTime)
                    {
                        this->acceptedMovies[i] = this->moviesList[i];
                        break;
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