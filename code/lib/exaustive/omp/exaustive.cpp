#include "exaustive.hpp"
#include <iostream>
#include <algorithm>

Exaustive::Exaustive()
{
    this->maxMoviesPerPermutation = new int(0);
    this->maxMovies = new int(-1);
    this->bestAgendaBitset = new std::bitset<24>;
}

Exaustive::~Exaustive()
{
    delete this->maxMoviesPerPermutation;
    delete this->maxMovies;
    delete this->bestAgendaBitset;
}

void Exaustive::showSelectedMovies()
{
    for (int i = 0; i < *this->movies; i++)
        if (this->bestAgendaBitset->test(i))
            std::cout << this->moviesList[i]->startTime << ' ' << this->moviesList[i]->endTime << ' ' << this->moviesList[i]->category << '\n';
    std::cout << "Max movies: " << *this->maxMovies << '\n';
}

void Exaustive::generatePermutations()
{
    int *movieCnt = new int();
    std::bitset<10> *permutation = new std::bitset<10>;
    int *maxMoviesPerCat_copy = new int[*this->categories];
    std::copy(this->maxMoviesPerCat, this->maxMoviesPerCat + *this->categories, maxMoviesPerCat_copy);

    bool isValid;
    int size = 1 << *this->movies;

    for (int i = 584; i < size; ++i)
    {
        isValid = 1;
        *movieCnt = 0;
        this->agendaBitset->reset();
        *this->acceptedMoviesCount = -1;
        for (int j = 0; j < *this->categories; j++)
            this->maxMoviesPerPermutation[j] = maxMoviesPerCat_copy[j];
            
        *permutation = std::bitset<10>(i);
        for (int j = 0; j < *this->movies; j++)
        {

            if (*permutation == std::bitset<10>{0000001111110}) std::cout << "i = " << i << '\n' << (*permutation == std::bitset<10>{0000001111110}) << '\n';
                std::cout << *permutation << ' ' << 
                *movieCnt << '\t' << 
                this->moviesList[j]->startTime << ' ' << 
                this->moviesList[j]->endTime << ' ' << 
                this->moviesList[j]->category << '\n';
            if (permutation->test(j) && this->movieIsValid(this->moviesList[j]))
            {
                // addMovieToAgenda(this->moviesList[j]);
                *this->agendaBitset |= *this->movieScheduleBitset;
                *movieCnt += 1;
            }
            else
            {
                isValid = 0;
                break;
            }
        }
        if (*movieCnt > *this->maxMovies && isValid)
        {
            *this->maxMovies = *movieCnt;
            *this->bestAgendaBitset = *this->agendaBitset;
        }
        break;
    }
    delete movieCnt;
    delete permutation;
    delete[] maxMoviesPerCat_copy;
}

void Exaustive::generateOutput()
{
    this->readMoviesCatalog();
    this->generatePermutations();
    // this->showSelectedMovies();
}

/*
5

 0 0 1 1 0





*/