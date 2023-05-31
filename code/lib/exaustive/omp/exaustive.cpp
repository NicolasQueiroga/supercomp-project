#include "exaustive.hpp"
#include <omp.h>
#include <iostream>
#include <algorithm>

OpenMp::OpenMp()
{
    this->maxMoviesPerCat_copy = new int[*this->categories];
    this->cnt = new int(0);
    this->max_cnt = new int(0);
    this->selectedMovie = new int(-1);
}

OpenMp::~OpenMp()
{
    delete[] this->maxMoviesPerCat_copy;
    delete this->cnt;
    delete this->max_cnt;
    delete this->selectedMovie;
}

void OpenMp::showSelectedMovies()
{
    std::cout << "MAX NUMBER OF MOVIES -> " << *this->cnt << '\n'
              << "SELECTED MOVIES:\n";
    for (int i = 0; i < *this->movies; i++)
        if (*this->selectedMovie & (1 << i))
            std::cout << this->moviesList[i]->startTime << " " << this->moviesList[i]->endTime << " " << this->moviesList[i]->category << '\n';
    std::cout << '\n';
}

void OpenMp::resetVariables()
{
    for (int i = 0; i < *this->categories; i++)
        this->maxMoviesPerCat[i] = this->maxMoviesPerCat_copy[i];
    this->agendaBitset->reset();
    *this->max_cnt = 0;
}

void OpenMp::generatePermutations()
{
    std::copy(this->maxMoviesPerCat, this->maxMoviesPerCat + *this->categories, this->maxMoviesPerCat_copy);
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < 1 << *this->movies; i++)
    {
        resetVariables();
        for (int j = 0; j < *this->movies; j++)
            if (i & (1 << j))
            {
                if (movieIsValid(this->moviesList[j]))
                {
                    *this->agendaBitset |= *this->movieScheduleBitset;
                    --this->maxMoviesPerCat[this->moviesList[j]->category - 1];
                    (*this->max_cnt)++;
                }
                else
                    break;
            }
#pragma omp critical
        {
            if (*this->max_cnt > *this->cnt)
            {
                *this->selectedMovie = i;
                *this->cnt = *this->max_cnt;
            }
        }
    }
}

void OpenMp::generateOutput()
{
    this->readMoviesCatalog();
    this->generatePermutations();
    this->showSelectedMovies();
}