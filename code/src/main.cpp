#include <exaustive/omp/exaustive.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    OpenMp *omp_ = new OpenMp();
    omp_->generateOutput();
    delete omp_;
    return 0;
}