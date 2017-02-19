#ifndef PROJET_TIMER_H
#define PROJET_TIMER_H

#include "sys/time.h"

class Timer {
private:
    struct timeval start_timeval;

public:
    void start();
    int elapsedTimeInMiliseconds();
    int elapsedTimeInSeconds();
    void reset();
};


#endif //PROJET_TIMER_H
