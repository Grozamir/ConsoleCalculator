#include "Data.hpp"

namespace calculator {

void OperationKey::Normalize() {
    if ( operation == EOperation::add ||
         operation == EOperation::mul ) {
        if ( numA < numB ) {
            std::swap( numA, numB );
        }
    }
}

OperationKey OperationKey::MakeFromRequestData( const RequestData& reqData ) {
    OperationKey operKey;
    operKey.operation = reqData.operation;
    operKey.numA = reqData.numA;
    operKey.numB = reqData.numB.value_or( 0 );
    operKey.Normalize();
    return operKey;
}

}  // namespace calculator
