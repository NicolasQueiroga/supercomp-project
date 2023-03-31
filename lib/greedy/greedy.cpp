#include "greedy.hpp"

void Greedy::scheduleMovies()
{
    int *i = new int(-1);
    while (++*i < *this->movies)
        if (this->movieIsValid(this->moviesList[*i]))
            this->addMovieToAgenda(this->moviesList[*i]);
    delete i;
}