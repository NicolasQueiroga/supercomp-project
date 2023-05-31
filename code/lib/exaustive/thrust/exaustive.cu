#include "exaustive.hpp"
#include <thrust/device_vector.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>
#include <thrust/iterator/counting_iterator.h>

__device__ bool Thrust::movieIsValid(const Movie *movie)
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

struct movie_validity_checker : public thrust::unary_function<int, bool>
{
    const Movie *moviesList;
    int *agendaBitset;
    int *movieScheduleBitset;
    int *maxMoviesPerCat;

    __device__ movie_validity_checker(const Movie *_moviesList, int *_agendaBitset, int *_movieScheduleBitset, int *_maxMoviesPerCat)
        : moviesList(_moviesList), agendaBitset(_agendaBitset), movieScheduleBitset(_movieScheduleBitset), maxMoviesPerCat(_maxMoviesPerCat) {}

    __device__ bool operator()(int j)
    {
        if (*agendaBitset & *movieScheduleBitset)
        {
            atomicSub(&maxMoviesPerCat[moviesList[j].category - 1], 1);
            return true;
        }
        return false;
    }
};

struct max_cnt_comparator
{
    __device__ bool operator()(const thrust::tuple<int, int> &x, const thrust::tuple<int, int> &y)
    {
        return thrust::get<1>(x) > thrust::get<1>(y);
    }
};

void Thrust::generatePermutations()
{
    thrust::device_vector<int> d_maxMoviesPerCat(maxMoviesPerCat, maxMoviesPerCat + *categories);
    thrust::device_vector<int> d_movieScheduleBitset(movieScheduleBitset, movieScheduleBitset + *movies);
    thrust::device_vector<Movie> d_moviesList(moviesList, moviesList + *movies);

    thrust::device_vector<int> d_max_cnt(1, 0);
    thrust::device_vector<int> d_selectedMovie(1, 0);
    thrust::device_vector<int> d_cnt(1, 0);

    thrust::device_vector<int> d_results(1 << *movies, 0);

    for (int i = 0; i < (1 << *movies); i++)
    {
        thrust::fill(d_maxMoviesPerCat.begin(), d_maxMoviesPerCat.end(), *categories);
        thrust::fill(d_results.begin(), d_results.end(), 0);
        d_max_cnt[0] = 0;

        thrust::counting_iterator<int> first(0);
        thrust::counting_iterator<int> last = first + *movies;
        thrust::transform(first, last, d_results.begin(), movie_validity_checker(thrust::raw_pointer_cast(d_moviesList.data()), thrust::raw_pointer_cast(d_agendaBitset.data()), thrust::raw_pointer_cast(d_movieScheduleBitset.data()), thrust::raw_pointer_cast(d_maxMoviesPerCat.data())));

        int max_cnt = thrust::reduce(d_results.begin(), d_results.end());

        if (max_cnt > d_cnt[0])
        {
            d_selectedMovie[0] = i;
            d_cnt[0] = max_cnt;
        }
    }

    thrust::copy(d_selectedMovie.begin(), d_selectedMovie.end(), selectedMovie);
    thrust::copy(d_cnt.begin(), d_cnt.end(), cnt);
}
