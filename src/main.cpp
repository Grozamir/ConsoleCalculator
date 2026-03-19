#include <cstdint>
#include <iostream>
#include <string>

#include "core/Logger.hpp"
#include "core/Runner.hpp"

// calculator '{"numA":5,"numB":2,"operation":"mul"}'

int main( int argc, char* argv[] ) {
    try {
        calculator::Runner runner{};
        runner.Run( argv[1] );
    } catch ( const std::exception& ex ) {
        calculator::Logger::Instance().Error( ex.what() );
    }
}
