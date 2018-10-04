#include "Timer.h"
#include <iostream>

Timer::Timer(std::string _title){
    title = _title;
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer(){
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration <double> delta = end - start;
    std::cout << "Operation \"" << title << "\" ended in " << delta.count() << " seconds\n";
}
