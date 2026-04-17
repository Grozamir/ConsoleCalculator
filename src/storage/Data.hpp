#pragma once

#include "core/Operation.hpp"
#include "core/RequestData.hpp"

namespace calculator {

struct OperationKey {
    EOperation operation = EOperation::none;
    int32_t numA = 0;
    int32_t numB = 0;

    void Normalize();

    static OperationKey MakeFromRequestData( const RequestData& reqData );

    bool operator==( const OperationKey& other ) const {
        return operation == other.operation && numA == other.numA && numB == other.numB;
    }
};

struct ResultOperation {
    int32_t calculateResult = 0;
    int32_t status = 0;
};

struct OperationKeyHash {
    size_t operator()( const OperationKey& k ) const {
        auto h1 = std::hash<int32_t>()( static_cast<int32_t>( k.operation ) );
        auto h2 = std::hash<int32_t>()( k.numA );
        auto h3 = std::hash<int32_t>()( k.numB );

        return h1 ^ ( h2 << 1 ) ^ ( h3 << 2 );
    }
};

}  // namespace calculator