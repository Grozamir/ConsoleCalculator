#include "Checker.hpp"

namespace calculator {

void Checker::Validate( const RequestData& requestData ) {
    if ( requestData.operation == EOperation::none ) {
        throw std::logic_error( "Invalid operation" );
    }

    if ( requestData.operation == EOperation::factorial ) {
        if ( requestData.numA <= 0 ) {
            throw std::logic_error( "Factorial requires positive number" );
        }
    }

    if ( requestData.operation != EOperation::factorial ) {
        if ( !requestData.numB.has_value() ) {
            throw std::invalid_argument( "Missing numB" );
        }
    }
}

}  // namespace calculator
