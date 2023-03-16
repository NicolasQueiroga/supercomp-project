#include "scheduler.hpp"
#include "IntervalTree.h"
#include <iostream>

Scheduler::Scheduler() {}
Scheduler::~Scheduler()
{
    for (int i = 0; i < *(this->categories); i++)
        delete this->maxMoviesPerCat[i];
    delete[] this->maxMoviesPerCat;

    for (int i = 0; i < *(this->movies); i++)
        delete this->moviesList[i];
    delete[] this->moviesList;

    delete this->movies;
    delete this->categories;
}

void Scheduler::readMoviesCatalog()
{
    this->movies = new int;
    this->categories = new int;
    std::cin >> *(this->movies) >> *(this->categories);

    int i = -1;
    this->maxMoviesPerCat = new int *[*(this->categories)];
    while (++i < *(this->categories))
    {
        this->maxMoviesPerCat[i] = new int;
        std::cin >> *(this->maxMoviesPerCat[i]);
    }

    i = -1;
    this->moviesList = new Movie *[*(this->movies)];
    int cat;
    short int startTime, endTime;
    while (++i < *(this->movies))
    {
        std::cin >> cat >> startTime >> endTime;
        this->moviesList[i] = new Movie;
        this->moviesList[i]->category = cat;
        this->moviesList[i]->startTime = startTime;
        this->moviesList[i]->endTime = endTime;
    }
}

void Scheduler::showVars()
{
    std::cout << "Movies: " << *(this->movies) << '\n';
    std::cout << "Categories: " << *(this->categories) << '\n';
    std::cout << "Max Movies Per Category: " << '\n';
    for (int i = 0; i < *(this->categories); i++)
        std::cout << *(this->maxMoviesPerCat[i]) << ' ';
    std::cout << '\n';
    std::cout << "Movies List: " << '\n';
    for (int i = 0; i < *(this->movies); i++)
        std::cout << this->moviesList[i]->category << ' ' << this->moviesList[i]->startTime << ' ' << this->moviesList[i]->endTime << '\n';
}

void Scheduler::createIntervalTree()
{
}