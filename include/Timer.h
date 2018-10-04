#ifndef TIMER_H
#define TIMER_H
#include <string>
#include <chrono>

class Timer{
    public:
        Timer(std::string _title);
        ~Timer();
    private:
        std::string title;
        std::chrono::high_resolution_clock::time_point start;
};

#endif // TIMER_H
