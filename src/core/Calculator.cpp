#include "Calculator.hpp"

namespace calculator {

int32_t Calculator::Calculate( const RequestData& requestData ) {
    switch ( requestData.operation ) {
        case EOperation::add: {
            return math.Add( requestData.numA, requestData.numB.value() );
        } break;
        case EOperation::sub: {
            return math.Sub( requestData.numA, requestData.numB.value() );
        } break;
        case EOperation::mul: {
            return math.Mul( requestData.numA, requestData.numB.value() );
        } break;
        case EOperation::div: {
            return math.Div( requestData.numA, requestData.numB.value() );
        } break;
        case EOperation::pow: {
            return math.Pow( requestData.numA, requestData.numB.value() );
        } break;
        case EOperation::factorial: {
            return math.Factorial( requestData.numA );
        } break;
        default:
            break;
    }
    throw std::logic_error( "Unknown operation" );
}

}  // namespace calculator
