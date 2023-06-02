#include "exaustive.hpp"
#include <thrust/device_vector.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>


Thrust::Thrust()
{
}

Thrust::~Thrust()
{
}

void Thrust::logic()
{
    thrust::device_vector<bool> d_agendaBitset(24);
    thrust::device_vector<bool> d_movieScheduleBitset(24);
    thrust::device_vector<int> d_moviesPerCat(*this->categories);
    thrust::device_vector<Movie *> d_movies(*this->movies);
}