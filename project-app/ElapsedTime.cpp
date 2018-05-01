#include "ElapsedTime.h"

double ElapsedTime(const timespec * const start, const timespec * const end)
{
    assert(0 != start);
    assert(0 != end);

    double time;
    time = (static_cast< double >(end->tv_sec - start->tv_sec) + (static_cast< double >(end->tv_nsec - start->tv_nsec) / 1000000000.0));

// std::cout << "Time: " << time << std::endl;
    return time;
}