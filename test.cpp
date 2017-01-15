#include "timer.h"

#include <limits>
#include <iostream>

int main()
{
    Timer t;
    for (uint32_t i = 0; i < std::numeric_limits<uint32_t>::max() / 10; ++i)
    {}
    std::cout << t.as<double, std::chrono::microseconds>() << std::endl;
    std::cout << t.as<int>() << std::endl;
    std::cout << t.as<std::string>() << std::endl;
    std::cout << t.as<std::string, std::chrono::seconds>() << std::endl;

    return 0;
}
