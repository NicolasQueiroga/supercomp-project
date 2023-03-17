#include "greedy.hpp"
#include <algorithm>

Greedy::Greedy()
{
    this->categoriesCount = new std::vector<int>(*(this->categories), 0);
    this->acceptedMovies = new Movie *[24];
    this->acceptedMoviesCount = new int;
    *(this->acceptedMoviesCount) = 0;
}

Greedy::~Greedy()
{
    delete this->categoriesCount;
    for (int i = 0; i < 24; i++)
        delete this->acceptedMovies[i];
    delete[] this->acceptedMovies;

    delete this->agenda;
    delete this->movieSchedule;
    delete this->acceptedMoviesCount;
}

void Greedy::normalSchedule()
{
    std::sort(this->moviesList, this->moviesList + *(this->movies), [](Movie *a, Movie *b)
              { return a->endTime < b->endTime; });

    this->agenda = new std::vector<bool>(24, 0);
    this->movieSchedule = new std::vector<bool>(24, 0);
    for (int i = 0; i < *(this->movies); i++)
    {
        if (this->moviesList[i]->startTime < this->moviesList[i]->endTime && this->moviesList[i]->startTime >= 0 && this->moviesList[i]->endTime < 24)
        {
            for (int j = this->moviesList[i]->startTime; j < this->moviesList[i]->endTime; j++)
                this->movieSchedule->at(j) = 1;

            if (std::equal(this->agenda->begin(), this->agenda->end(), this->movieSchedule->begin(), [](bool a, bool b)
                           { return !(a & b); }) &&
                this->categoriesCount->at(this->moviesList[i]->category - 1) <= *(this->maxMoviesPerCat[this->moviesList[i]->category - 1]))
            {
                this->acceptedMovies[++*(this->acceptedMoviesCount)] = this->moviesList[i];
                this->categoriesCount->at(this->moviesList[i]->category - 1)++;
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
    for (int i = 0; i < *(this->acceptedMoviesCount); i++)
        std::cout << this->acceptedMovies[i]->category << ' ' << this->acceptedMovies[i]->startTime << ' ' << this->acceptedMovies[i]->endTime << '\n';
}