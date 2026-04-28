#include <cstdint>

#include "core/Logger.hpp"
#include "core/Service.hpp"

int main( int argc, char* argv[] ) {
    try {
        calculator::Service service;
        service.Start();
        service.Wait();
    } catch ( const std::exception& ex ) {
        calculator::Logger::Instance().Error( ex.what() );
    }
}
