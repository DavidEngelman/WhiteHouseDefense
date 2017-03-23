#include <exception>
#include <stdexcept>
#include "Timer.hpp"

Timer::Timer(): numOfElapsedMilisecondsInPreviousIntervals(0), isPaused(true) {}

void Timer::start() {
    gettimeofday(&last_pause_timeval, 0);
    isPaused = false;
}

void Timer::reset() {
    numOfElapsedMilisecondsInPreviousIntervals = 0;
    isPaused = false;
    start();
}

void Timer::pause() {
    numOfElapsedMilisecondsInPreviousIntervals += getMilisecondsSinceLastCurrentIntervalStart();
    isPaused = true;
}

void Timer::resume() {
    gettimeofday(&last_pause_timeval, 0);
    isPaused = false;
}

int Timer::elapsedTimeInMiliseconds() {
    if (isPaused) throw std::logic_error("Timer is paused");
    return numOfElapsedMilisecondsInPreviousIntervals + getMilisecondsSinceLastCurrentIntervalStart();
}

int Timer::elapsedTimeInSeconds() {
    return elapsedTimeInMiliseconds() / 1000;
}

int Timer::getMilisecondsSinceLastCurrentIntervalStart() {
    struct timeval current_timeval;
    gettimeofday(&current_timeval, 0);

    double elapsedTimeInMilliseconds = (current_timeval.tv_sec - last_pause_timeval.tv_sec) * 1000;
    elapsedTimeInMilliseconds += (current_timeval.tv_usec - last_pause_timeval.tv_usec) / 1000;
    return (int) elapsedTimeInMilliseconds;
}
