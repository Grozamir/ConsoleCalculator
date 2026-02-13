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

EOperation ConvertStrToOperation( const char* str ) {
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
                 "  -a, --numberA=<int>         Firstrd.numBer\n"
                 "  -b, --numberB=<int>         Secondrd.numBer (not needed for factorial)\n";
}

struct RuntimeData {
    int32_t numA = 0;
    int32_t numB = 0;
    EOperation selectedOperation = EOperation::none;
    int32_t result = 0;
};

bool Parse( int argc, char* argv[], RuntimeData& rd ) {
    static struct option long_options[] = {
        { "help", no_argument, nullptr, 'h' },
        { "operation", required_argument, nullptr, 'o' },
        { "numberA", required_argument, nullptr, 'a' },
        { "numberB", required_argument, nullptr, 'b' },
        { nullptr, 0, nullptr, 0 } };

    int option_index = 0;
    while ( true ) {
        auto optRes = getopt_long( argc, argv, "ho:a:b:", long_options, &option_index );
        if ( optRes == -1 ) {
            break;
        }

        switch ( optRes ) {
            case 'h':
                PrintHelp();
                return false;
            case 'o':
                rd.selectedOperation = ConvertStrToOperation( optarg );
                break;
            case 'a': {
                rd.numA = atoi( optarg );
            } break;
            case 'b': {
                rd.numB = atoi( optarg );
            } break;
            default:
                break;
        }
    }

    return true;
}

bool CheckNumbersAndOperation( const RuntimeData& rd ) {
    if ( rd.selectedOperation == EOperation::none ) {
        std::cout << "Not valid operation!" << '\n';
        return false;
    }

    if ( rd.selectedOperation == EOperation::factorial ) {
        if ( rd.numA <= 0 ) {
            std::cout << "numberA less or equal 0!" << '\n';
            return false;
        }
    }

    return true;
}

bool Calculate( RuntimeData& rd ) {
    switch ( rd.selectedOperation ) {
        case EOperation::add: {
            if ( !mathlib::add( rd.numA, rd.numB, rd.result ) ) {
                std::cout << "Invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        case EOperation::sub: {
            if ( !mathlib::sub( rd.numA, rd.numB, rd.result ) ) {
                std::cout << "Invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        case EOperation::mul: {
            if ( !mathlib::mul( rd.numA, rd.numB, rd.result ) ) {
                std::cout << "Invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        case EOperation::div: {
            if ( !mathlib::div( rd.numA, rd.numB, rd.result ) ) {
                std::cout << "Division by zero or invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        case EOperation::pow: {
            if ( !mathlib::pow( rd.numA, rd.numB, rd.result ) ) {
                std::cout << "Invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        case EOperation::factorial: {
            if ( !mathlib::factorial( rd.numA, rd.result ) ) {
                std::cout << "Invalidrd.numBer!" << '\n';
                return false;
            }
        } break;
        default:
            break;
    }
    return true;
}

void PrintResult( const RuntimeData& rd ) {
    std::cout << "Result: " << rd.result << '\n';
}

void Run( int argc, char* argv[] ) {
    RuntimeData rd;
    if ( !Parse( argc, argv, rd ) ) {
        return;
    }
    if ( !CheckNumbersAndOperation( rd ) ) {
        return;
    }
    if ( !Calculate( rd ) ) {
        return;
    }
    PrintResult( rd );
}

int main( int argc, char* argv[] ) {
    Run( argc, argv );
}
