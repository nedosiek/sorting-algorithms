#ifndef AIZO_1_TIMER_H
#define AIZO_1_TIMER_H

#include <chrono>
#include <ctime>

using namespace std;

class Timer{
public:
    Timer();
    void reset();
    int start();
    int stop();
    int result();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool is_running = false;
};

#endif
