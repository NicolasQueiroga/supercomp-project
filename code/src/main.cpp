#include <exaustive/omp/exaustive.hpp>
#include <exaustive/thrust/exaustive.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    // OpenMp *omp_ = new OpenMp();
    // omp_->generateOutput();
    // delete omp_;

    Thrust *thrust_ = new Thrust();
    thrust_->generateOutput();
    delete thrust_;

    return 0;
}