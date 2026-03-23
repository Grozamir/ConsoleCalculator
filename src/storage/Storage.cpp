#include "Storage.hpp"

#include <string>

#include "core/Logger.hpp"

#include "postgres/Work.hpp"

namespace calculator {

void Storage::Init() {
    const std::string conninfo = "host=localhost dbname=postgres user=grozdb password=654321";
    connDb = std::make_unique<pg::Connection>( conninfo );
}

void Storage::WarmUpCache() {
    pg::Work workDb( connDb );
    auto result = workDb.Exec( "SELECT a_num, b_num, operation, result, status FROM calculator" );

    if ( PQresultStatus( result.get() ) != PGRES_TUPLES_OK ) {
        return;
    }

    for ( int i = 0; i < PQntuples( result.get() ); ++i ) {
        OperationKey operKey;
        operKey.operation = static_cast<EOperation>( std::stoi( PQgetvalue( result.get(), i, 2 ) ) );
        operKey.numA = std::stoi( PQgetvalue( result.get(), i, 0 ) );
        operKey.numB = std::stoi( PQgetvalue( result.get(), i, 1 ) );
        operKey.Normalize();

        ResultOperation resOper;
        resOper.calculateResult = std::stoi( PQgetvalue( result.get(), i, 3 ) );
        resOper.status = std::stoi( PQgetvalue( result.get(), i, 4 ) );

        cache.data[operKey] = resOper;
    }
}

std::optional<ResultOperation> Storage::FindResult( const OperationKey& operationKey ) {
    if ( auto findRes = cache.data.find( operationKey ); findRes != cache.data.end() ) {
        return findRes->second;
    }

    return std::nullopt;
}

std::optional<ResultOperation> Storage::FindResultByRequestData( const RequestData& requestData ) {
    auto operationKey = OperationKey::MakeFromRequestData( requestData );
    return FindResult( operationKey );
}

void Storage::AddCalculatorResult( const OperationKey& operationKey, const ResultOperation& resultOperation ) {
    cache.data[operationKey] = resultOperation;

    const std::vector<std::string> paramStrings = {
        std::to_string( operationKey.numA ),
        std::to_string( operationKey.numB ),
        std::to_string( static_cast<int32_t>( operationKey.operation ) ),
        std::to_string( resultOperation.calculateResult ),
        std::to_string( resultOperation.status ) };

    const std::string command =
        "INSERT INTO calculator (a_num, b_num, operation, result, status) "
        "VALUES ($1, $2, $3, $4, $5)";

    pg::Work workDb( connDb );
    auto result = workDb.ExecParams( command, paramStrings );

    if ( PQresultStatus( result.get() ) != PGRES_COMMAND_OK ) {
        Logger::Instance().Error( "Insert failed:" );
        Logger::Instance().Error( PQerrorMessage( connDb->Get() ) );
    }
}

void Storage::AddCalculatorResult( const OperationKey& operationKey, int32_t result ) {
    AddCalculatorResult( operationKey, ResultOperation{ .calculateResult = result, .status = 0 } );
}

void Storage::AddFailCalculatorResult( const OperationKey& operationKey, int32_t statusProblem ) {
    AddCalculatorResult( operationKey, ResultOperation{ .calculateResult = 0, .status = statusProblem } );
}

}  // namespace calculator
