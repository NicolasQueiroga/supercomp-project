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
    for (int i = 0; i < *(this->movies); i++)
        this->intervals.push_back(Interval<int, Movie *>(this->moviesList[i]->startTime, this->moviesList[i]->endTime, this->moviesList[i]));

    this->intervalTree = IntervalTree<int, Movie *>(this->intervals);
}

void Greedy::showAcceptedMovies()
{
    int i = -1;
    while (this->acceptedMovies[++i] != nullptr)
        std::cout << this->acceptedMovies[i]->category << ' ' << this->acceptedMovies[i]->startTime << ' ' << this->acceptedMovies[i]->endTime << '\n';
}