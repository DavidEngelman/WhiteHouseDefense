#ifndef PROJET_TIMER_H
#define PROJET_TIMER_H

#include "sys/time.h"

class Timer {
private:
    struct timeval last_pause_timeval;
    int numOfElapsedMilisecondsInPreviousIntervals;
    bool isPaused;

    int getMilisecondsSinceLastCurrentIntervalStart();

public:
    Timer();

    void start();
    void pause();
    void resume();
    void reset();

    int elapsedTimeInSeconds();
    int elapsedTimeInMiliseconds();
};


#endif //PROJET_TIMER_H
