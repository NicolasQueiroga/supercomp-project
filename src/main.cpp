#include "greedy/greedy.hpp"
#include "random/random.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argv[1][0] == '1')
    {
        Random random = Random();
        random.generateOutput();
        random.showAcceptedMovies();
    }
    else if (argv[1][0] == '0')
    {
        Greedy greedy = Greedy();
        greedy.generateOutput();
        greedy.showAcceptedMovies();
    }
    return 0;
}