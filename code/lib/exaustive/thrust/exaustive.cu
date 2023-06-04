#include "exaustive.hpp"
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/functional.h>
#include <thrust/reduce.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>
#include <thrust/execution_policy.h>

Thrust::Thrust()
{
}

Thrust::~Thrust()
{
}

struct BitWiseAnd
{
    __device__ bool operator()(const bool &x, const bool &y)
    {
        return x & y;
    }
};

struct BitWiseOr
{
    __device__ bool operator()(const bool &x, const bool &y)
    {
        return x | y;
    }
};

struct Thrust::MovieCount
{
    thrust::device_ptr<Scheduler> d_scheduler_ptr;
    int *movies;
    int *categories;
    thrust::device_vector<bool> d_agendaBitset;
    thrust::device_vector<bool> d_movieScheduleBitset;
    thrust::device_vector<int> d_maxMoviesPerCat;
    thrust::device_vector<Movie *> d_moviesList;

    thrust::device_vector<int> d_maxMoviesPerCat_copy;
    thrust::device_vector<int> d_probabilitiySum;

    MovieCount(
        thrust::device_ptr<Scheduler> &d_scheduler_ptr,
        int *movies,
        int *categories,
        thrust::device_vector<bool> &d_agendaBitset,
        thrust::device_vector<bool> &d_movieScheduleBitset,
        thrust::device_vector<int> &d_maxMoviesPerCat,
        thrust::device_vector<Movie *> &d_moviesList) : d_scheduler_ptr(d_scheduler_ptr),
                                                        movies(movies),
                                                        categories(categories),
                                                        d_agendaBitset(d_agendaBitset),
                                                        d_movieScheduleBitset(d_movieScheduleBitset),
                                                        d_maxMoviesPerCat(d_maxMoviesPerCat),
                                                        d_moviesList(d_moviesList)
    {
        d_probabilitiySum.resize(1 << *movies);
        d_maxMoviesPerCat_copy.resize(*categories);
    }

    __host__ __device__ bool movieIsValid(Movie *movie)
    {
        thrust::fill(d_movieScheduleBitset.begin(), d_movieScheduleBitset.end(), false);
        for (short j = movie->startTime; j < movie->endTime; j++)
            d_movieScheduleBitset[j] = true;

        thrust::transform(
            d_agendaBitset.begin(),
            d_agendaBitset.end(),
            d_movieScheduleBitset.begin(),
            d_agendaBitset.begin(),
            BitWiseAnd());

        bool anyOverlap = thrust::reduce(
            d_agendaBitset.begin(),
            d_agendaBitset.end(),
            false,
            BitWiseOr());

        if ((!anyOverlap && d_maxMoviesPerCat[movie->category - 1] > 0) &&
            (movie->startTime < movie->endTime && movie->startTime >= 0 && movie->endTime < 24))
            return true;
        return false;
    }

    __host__ __device__ int operator()(const int &i)
    {
        thrust::fill(d_agendaBitset.begin(), d_agendaBitset.end(), false);
        thrust::copy(d_maxMoviesPerCat.begin(), d_maxMoviesPerCat.end(), d_maxMoviesPerCat_copy.begin());
        int sum = 0;
        for (int j = 0; j < *this->movies; j++)
            if (i & (1 << j))
            {
                if (movieIsValid(d_moviesList[j]))
                {
                    thrust::transform(
                        d_agendaBitset.begin(),
                        d_agendaBitset.end(),
                        d_movieScheduleBitset.begin(),
                        d_agendaBitset.begin(),
                        BitWiseOr());

                    Movie *movie = d_moviesList[j];
                    d_maxMoviesPerCat[movie->category - 1]--;
                    sum++;               
                }
                else
                    break;
            }

        return sum;
    }
};

void Thrust::scheduleMovies()
{
    this->readMoviesCatalog();
    thrust::device_vector<bool> d_agendaBitset(24);
    thrust::device_vector<bool> d_movieScheduleBitset(24);
    thrust::device_vector<int> d_maxMoviesPerCat(this->maxMoviesPerCat, this->maxMoviesPerCat + *this->categories);
    thrust::device_vector<int> d_maxMoviesPerCat_copy(d_maxMoviesPerCat);
    thrust::device_vector<int> d_possibilities(1 << *this->movies);
    thrust::device_vector<int> d_validSchedules(d_possibilities.size());
    thrust::device_vector<Movie *> d_moviesList(this->moviesList, this->moviesList + *this->movies);
    thrust::device_ptr<int> d_movies_ptr = thrust::device_pointer_cast(this->movies);
    thrust::device_ptr<int> d_categories_ptr = thrust::device_pointer_cast(this->categories);

    thrust::sequence(d_possibilities.begin(), d_possibilities.end());
    thrust::fill(d_agendaBitset.begin(), d_agendaBitset.end(), false);
    thrust::fill(d_movieScheduleBitset.begin(), d_movieScheduleBitset.end(), false);

    // validity check for each variable
    thrust::host_vector<bool> h_agendaBitset = d_agendaBitset;
    thrust::host_vector<bool> h_movieScheduleBitset = d_movieScheduleBitset;
    thrust::host_vector<int> h_maxMoviesPerCat = d_maxMoviesPerCat;
    thrust::host_vector<int> h_maxMoviesPerCat_copy = d_maxMoviesPerCat_copy;
    thrust::host_vector<int> h_possibilities = d_possibilities;
    thrust::host_vector<int> h_validSchedules = d_validSchedules;
    thrust::host_vector<Movie *> h_moviesList = d_moviesList;

    // cout's
    std::cout << "Agenda Bitset: ";
    for (int i = 0; i < h_agendaBitset.size(); i++)
        std::cout << h_agendaBitset[i] << " ";
    std::cout << std::endl;

    std::cout << "Movie Schedule Bitset: ";
    for (int i = 0; i < h_movieScheduleBitset.size(); i++)
        std::cout << h_movieScheduleBitset[i] << " ";
    std::cout << std::endl;

    std::cout << "Max Movies Per Category: ";
    for (int i = 0; i < h_maxMoviesPerCat.size(); i++)
        std::cout << h_maxMoviesPerCat[i] << " ";
    std::cout << std::endl;

    std::cout << "Max Movies Per Category Copy: ";
    for (int i = 0; i < h_maxMoviesPerCat_copy.size(); i++)
        std::cout << h_maxMoviesPerCat_copy[i] << " ";
    std::cout << std::endl;

    std::cout << "Possibilities: ";
    for (int i = 0; i < h_possibilities.size(); i++)
        std::cout << h_possibilities[i] << " ";
    std::cout << std::endl;

    std::cout << "Valid Schedules: ";
    for (int i = 0; i < h_validSchedules.size(); i++)
        std::cout << h_validSchedules[i] << " ";
    std::cout << std::endl;

    std::cout << "Movies List: ";
    for (int i = 0; i < h_moviesList.size(); i++)
        std::cout << h_moviesList[i]->id << " ";
    std::cout << std::endl;

    thrust::device_ptr<Scheduler> d_scheduler_ptr = thrust::device_pointer_cast(this);
    MovieCount mc = MovieCount(d_scheduler_ptr, this->movies, this->categories, d_agendaBitset, d_movieScheduleBitset, d_maxMoviesPerCat, d_moviesList);
    thrust::transform(d_possibilities.begin(), d_possibilities.end(), d_possibilities.begin(), mc);

    // cout's
    thrust::host_vector<int> h_validSchedules2 = d_possibilities;
    std::cout << "Valid Schedules: ";
    for (int i = 0; i < h_validSchedules2.size(); i++)
        std::cout << h_validSchedules2[i] << " ";
    std::cout << std::endl;

}

void Thrust::generateOutput()
{
    this->readMoviesCatalog();
    this->scheduleMovies();
}