#include "greedy.hpp"
#include <algorithm>
#include <iostream>
using std::cout;

Greedy::Greedy()
{
    this->acceptedMovies = new Movie *[24];
    for (int i = 0; i < 24; i++)
        this->acceptedMovies[i] = new Movie;
    this->acceptedMoviesCount = new int;
    *(this->acceptedMoviesCount) = -1;
    this->agendaBitset = new std::bitset<24>;
    this->movieScheduleBitset = new std::bitset<24>;
}

Greedy::~Greedy()
{
    for (int i = 0; i < 24; i++)
        delete this->acceptedMovies[i];
    delete[] this->acceptedMovies;

    delete this->acceptedMoviesCount;
    delete this->agendaBitset;
    delete this->movieScheduleBitset;
}

void Greedy::normalSchedule()
{
    std::sort(this->moviesList, this->moviesList + *this->movies, [](Movie *a, Movie *b)
              { return a->endTime < b->endTime; });

    for (int i = 0; i < *(this->movies); i++)
    {
        this->movieScheduleBitset->reset();
        if (this->moviesList[i]->startTime < this->moviesList[i]->endTime && this->moviesList[i]->startTime >= 0 && this->moviesList[i]->endTime < 24)
        {
            for (int j = this->moviesList[i]->startTime; j < this->moviesList[i]->endTime; j++)
                this->movieScheduleBitset->set(j);

            if (!(*this->movieScheduleBitset & *this->agendaBitset).any() &&
                *this->maxMoviesPerCat[this->moviesList[i]->category - 1] > 0)
            {
                *this->agendaBitset |= *this->movieScheduleBitset;
                this->acceptedMovies[++*this->acceptedMoviesCount] = this->moviesList[i];
                --*this->maxMoviesPerCat[this->moviesList[i]->category - 1];
            }
        }
    }
}

void Greedy::optimizedSchedule()
{
    // for (int i = 0; i < *(this->movies); i++)
    //     this->intervals.push_back(Interval<int, int>(this->moviesList[i]->startTime, this->moviesList[i]->endTime, this->moviesList[i]));

    // this->intervalTree = IntervalTree<int, int>(this->intervals);
}

void Greedy::showAcceptedMovies()
{
    for (int i = 0; i <= *this->acceptedMoviesCount; i++)
        std::cout << this->acceptedMovies[i]->startTime << ' ' << this->acceptedMovies[i]->endTime << ' ' << this->acceptedMovies[i]->category << '\n';
}