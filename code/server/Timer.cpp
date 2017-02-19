#include "Timer.h"

void Timer::start() {
    gettimeofday(&start_timeval, 0);
}

void Timer::reset() {
    start();
}

int Timer::elapsedTimeInMiliseconds() {
    struct timeval current_timeval;
    gettimeofday(&current_timeval, 0);

    double elapsedTimeInMilliseconds = (current_timeval.tv_sec - start_timeval.tv_sec) * 1000;
    return (int) elapsedTimeInMilliseconds;
}

int Timer::elapsedTimeInSeconds() {
    return elapsedTimeInMiliseconds() / 1000;
}
