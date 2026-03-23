#pragma once

#include "cache/Cache.hpp"

#include "postgres/Connection.hpp"

namespace calculator {

class Storage {
public:
    void Init();
    void WarmUpCache();

    std::optional<ResultOperation> FindResult( const OperationKey& operationKey );
    std::optional<ResultOperation> FindResultByRequestData( const RequestData& requestData );

    void AddCalculatorResult( const OperationKey& operationKey, const ResultOperation& resultOperation );
    void AddCalculatorResult( const OperationKey& operationKey, int32_t result );
    void AddFailCalculatorResult( const OperationKey& operationKey, int32_t statusProblem );

private:
    Cache cache;

    std::shared_ptr<pg::Connection> connDb;
};
}  // namespace calculator