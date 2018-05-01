#ifndef ELAPSEDTIME_H
#define ELAPSEDTIME_H

#include <sys/time.h>
#include <cassert>
#include <time.h>
#include <iostream>

#define NSECTOUSEC 1000

extern double ElapsedTime(const timespec * const start, const timespec * const end);

#endif /* ELAPSEDTIME_H */
