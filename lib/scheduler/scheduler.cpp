#include "scheduler.hpp"
#include "IntervalTree.h"
#include <iostream>

Scheduler::Scheduler()
{
    this->movies = new int;
    this->categories = new int;
    this->categoriesCount = new int *[24];
    for (int i = 0; i < 24; i++)
    {
        this->categoriesCount[i] = new int;
        *this->categoriesCount[i] = 0;
    }
}

Scheduler::~Scheduler()
{
    delete this->movies;
    delete this->categories;

    for (int i = 0; i < 24; i++)
        delete this->categoriesCount[i];
    delete[] this->categoriesCount;

    for (int i = 0; i < *(this->categories); i++)
        delete this->maxMoviesPerCat[i];
    delete[] this->maxMoviesPerCat;

    for (int i = 0; i < *(this->movies); i++)
        delete this->moviesList[i];
    delete[] this->moviesList;


}

void Scheduler::readMoviesCatalog()
{
    std::cin >> *this->movies >> *this->categories;
    this->maxMoviesPerCat = new int *[*this->categories];
    this->moviesList = new Movie *[*this->movies];

    int i = -1;
    while (++i < *this->categories)
    {
        this->maxMoviesPerCat[i] = new int;
        std::cin >> *this->maxMoviesPerCat[i];
    }

    i = -1;
    int cat;
    short int startTime, endTime;
    while (++i < *this->movies)
    {
        std::cin >> startTime >> endTime >> cat;
        this->moviesList[i] = new Movie;
        this->moviesList[i]->category = cat;
        this->moviesList[i]->startTime = startTime;
        this->moviesList[i]->endTime = endTime;
    }
}

void Scheduler::showVars()
{
    std::cout << "Movies: " << *this->movies << '\n';
    std::cout << "Categories: " << *this->categories << '\n';
    std::cout << "Max Movies Per Category: " << '\n';
    for (int i = 0; i < *this->categories; i++)
        std::cout << *this->maxMoviesPerCat[i] << ' ';
    std::cout << '\n';
    std::cout << "Movies List: " << '\n';
    for (int i = 0; i < *this->movies; i++)
        std::cout << this->moviesList[i]->startTime << ' ' << this->moviesList[i]->endTime << ' ' << this->moviesList[i]->category << '\n';
}