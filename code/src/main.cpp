#include <exaustive/omp/exaustive.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    Exaustive *exaustive = new Exaustive();
    exaustive->generateOutput();
    delete exaustive;
    return 0;
}