#include "scheduler.hpp"
#include <algorithm>
#include <iostream>

Scheduler::Scheduler()
{
    this->movies = new int;
    this->categories = new int;

    this->acceptedMovies = new Movie *[24];
    this->acceptedMoviesCount = new int(-1);
    this->agendaBitset = new std::bitset<24>;
    this->movieScheduleBitset = new std::bitset<24>;

    this->moviesList = nullptr;
    this->maxMoviesPerCat = nullptr;
}

Scheduler::~Scheduler()
{
    for (int i = 0; i < *this->movies; i++)
        delete this->moviesList[i];
    delete[] this->moviesList;

    delete this->movies;
    delete this->categories;
    delete[] this->maxMoviesPerCat;
    delete[] this->acceptedMovies;

    delete this->acceptedMoviesCount;
    delete this->agendaBitset;
    delete this->movieScheduleBitset;
}

void Scheduler::readMoviesCatalog()
{
    std::cin >> *this->movies >> *this->categories;
    this->maxMoviesPerCat = new int[*this->categories];
    this->moviesList = new Movie *[*this->movies];

    int i = -1;
    while (++i < *this->categories)
        std::cin >> this->maxMoviesPerCat[i];

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
    std::sort(this->moviesList, this->moviesList + *this->movies, [](Movie *a, Movie *b)
              {
        if (a->endTime == b->endTime)
            return a->startTime < b->startTime;
        return a->endTime < b->endTime; });
}

void Scheduler::showVars()
{
    std::cout << "Movies: " << *this->movies << '\n';
    std::cout << "Categories: " << *this->categories << '\n';
    std::cout << "Max Movies Per Category: " << '\n';
    for (int i = 0; i < *this->categories; i++)
        std::cout << this->maxMoviesPerCat[i] << ' ';
    std::cout << '\n';
    std::cout << "Movies List: " << '\n';
    for (int i = 0; i < *this->movies; i++)
        std::cout << this->moviesList[i]->startTime << ' ' << this->moviesList[i]->endTime << ' ' << this->moviesList[i]->category << '\n';
}

bool Scheduler::movieIsValid(Movie *movie)
{
    this->movieScheduleBitset->reset();
    for (short j = movie->startTime; j < movie->endTime; j++)
        this->movieScheduleBitset->set(j);

    if ((!(*this->movieScheduleBitset & *this->agendaBitset).any() &&
         this->maxMoviesPerCat[movie->category - 1] > 0) &&
        (movie->startTime < movie->endTime && movie->startTime >= 0 && movie->endTime < 24))
        return 1;

    return 0;
}

void Scheduler::addMovieToAgenda(Movie *movie)
{
    *this->agendaBitset |= *this->movieScheduleBitset;
    this->acceptedMovies[++*this->acceptedMoviesCount] = movie;
    --this->maxMoviesPerCat[movie->category - 1];
}

void Scheduler::showAcceptedMovies()
{
    std::sort(this->acceptedMovies, this->acceptedMovies + *this->acceptedMoviesCount, [](Movie *a, Movie *b)
              {
        if (a->endTime == b->endTime)
            return a->startTime < b->startTime;
        return a->endTime < b->endTime; });
    for (int i = 0; i <= *this->acceptedMoviesCount; i++)
        std::cout << this->acceptedMovies[i]->startTime << ' ' << this->acceptedMovies[i]->endTime << ' ' << this->acceptedMovies[i]->category << '\n';
}