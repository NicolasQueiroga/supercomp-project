#include "greedy.hpp"

void Greedy::scheduleMovies()
{
    for (int i = 0; i < *(this->movies); i++)
        if (this->movieIsValid(this->moviesList[i]))
            this->addMovieToAgenda(this->moviesList[i]);
}