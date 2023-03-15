#pragma once

class Scheduler
{
private:
public:
    Scheduler();
    virtual void sortMovies();
    static void generateInput(int *n, int *m);
};