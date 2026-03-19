#include "Printer.hpp"

#include <iostream>

namespace calculator {

void Printer::PrintResult( int32_t result ) {
    std::cout << result << '\n';
}

}  // namespace calculator