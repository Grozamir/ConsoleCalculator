#include <cstdint>
#include <cstring>
#include <iostream>

#include <getopt.h>

#include "SimpleMath.hpp"

enum class EOperation : uint8_t {
    none,
    add,
    sub,
    mul,
    div,
    pow,
    factorial,
};

EOperation ConvertStrToOperation( const char *str ) {
    if ( strcmp( str, "add" ) == 0 )
        return EOperation::add;
    if ( strcmp( str, "sub" ) == 0 )
        return EOperation::sub;
    if ( strcmp( str, "mul" ) == 0 )
        return EOperation::mul;
    if ( strcmp( str, "div" ) == 0 )
        return EOperation::div;
    if ( strcmp( str, "pow" ) == 0 )
        return EOperation::pow;
    if ( strcmp( str, "factorial" ) == 0 )
        return EOperation::factorial;

    return EOperation::none;
}

void PrintHelp() {
    std::cout << "Options:\n"
                 "  -h, --help                  Show help\n"
                 "  -o, --operation=<string>    add | sub | mul | div | pow | factorial\n"
                 "  -a, --numberA=<int>         First number\n"
                 "  -b, --numberB=<int>         Second number (not needed for factorial)\n";
}

int main( int argc, char *argv[] ) {
    static struct option long_options[] = {
        { "help", no_argument, nullptr, 'h' },
        { "operation", required_argument, nullptr, 'o' },
        { "numberA", required_argument, nullptr, 'a' },
        { "numberB", required_argument, nullptr, 'b' },
        { nullptr, 0, nullptr, 0 } };

    int option_index = 0;

    int32_t numA = 0;
    int32_t numB = 0;
    EOperation selectedOperation = EOperation::none;
    while ( true ) {
        auto optRes = getopt_long( argc, argv, "ho:a:b:", long_options, &option_index );
        if ( optRes == -1 ) {
            break;
        }

        switch ( optRes ) {
            case 'h':
                PrintHelp();
                return 0;
            case 'o':
                selectedOperation = ConvertStrToOperation( optarg );
                if ( selectedOperation == EOperation::none ) {
                    std::cout << "Not valid operation!" << '\n';
                    return 1;
                }
                break;
            case 'a': {
                numA = atoi( optarg );
            } break;
            case 'b': {
                numB = atoi( optarg );
            } break;
            default:
                break;
        }
    }

    int32_t result = 0;

    switch ( selectedOperation ) {
        case EOperation::add: {
            result = mathlib::add( numA, numB );
        } break;
        case EOperation::sub: {
            result = mathlib::sub( numA, numB );
        } break;
        case EOperation::mul: {
            result = mathlib::mul( numA, numB );
        } break;
        case EOperation::div: {
            if ( !mathlib::div( numA, numB, result ) ) {
                std::cout << "Division by zero!" << '\n';
                return 1;
            }
        } break;
        case EOperation::pow: {
            result = mathlib::pow( numA, numB );
        } break;
        case EOperation::factorial: {
            if ( numA > 0 ) {
                result = mathlib::factorial( numA );
            } else {
                std::cout << "numberA less or equal 0!" << '\n';
                return 1;
            }
        } break;
        default:
            break;
    }

    std::cout << "Result: " << result << '\n';
}