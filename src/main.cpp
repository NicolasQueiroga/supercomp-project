#include "greedy/greedy.hpp"
#include "random/random.hpp"

int main(int argc, char **argv)
{
    if (argv[3][0] == '1')
    {
        Random random = Random();
        random.readMoviesCatalog();
        random.scheduleMovies();
        random.showAcceptedMovies();
    }
    else if (argv[3][0] == '0')
    {
        Greedy greedy = Greedy();
        greedy.readMoviesCatalog();
        greedy.scheduleMovies();
        greedy.showAcceptedMovies();
    }
    return 0;
}