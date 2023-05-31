#include "exaustive.hpp"
#include <iostream>
#include <algorithm>

Exaustive::Exaustive()
{
    this->possibilities = new std::vector<Movie>(1 << *this->movies);
    this->maxMoviesPerCat_copy = new int[*this->categories];
    std::copy(this->maxMoviesPerCat, this->maxMoviesPerCat + *this->categories, this->maxMoviesPerCat_copy);
    this->cnt = new int(0);
}

Exaustive::~Exaustive()
{
    delete this->possibilities;
    delete[] this->maxMoviesPerCat_copy;
    delete this->cnt;
}

void Exaustive::showSelectedMovies()
{
}

void resetVariables()
{
    for (int i = 0; i < *this->categories; i++)
        this->maxMoviesPerCat[i] = this->maxMoviesPerCat_copy[i];
    this->agendaBitset->reset();
    *this->acceptedMoviesCount = -1;
    this->acceptedMovies = new Movie *[24];
}

void Exaustive::generatePermutations()
{
    int max_cnt = 0;
    for (int i = 0; i < 1 << *this->movies; i++)
    {
        for (int j = 0; j < *this->movies; j++)
            if (i & (1 << j))
            {
                if (movieIsValid(this->moviesList[j]))
                {
                    addMovieToAgenda(this->moviesList[j]);
                    max_cnt++;
                }
                else break;
            }
            
        if (max_cnt > *this->cnt)
            *this->cnt = max_cnt;

        resetVariables();
        max_cnt = 0;
    }
    std::cout << "MAX: " << *this->cnt << std::endl;
}

void Exaustive::generateOutput()
{
    this->readMoviesCatalog();
    this->generatePermutations();
    this->showSelectedMovies();
}