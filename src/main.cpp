#include <cstdint>
#include <iostream>
#include <string>

#include "core/Runner.hpp"

// {"numA":5,"numB":2,"operation":"mul"}

int main() {
    std::cout << "Enter parameter via json: ";

    std::string inputStr;
    std::getline( std::cin, inputStr );

    Runner runner{};
    runner.Run( inputStr );
}
