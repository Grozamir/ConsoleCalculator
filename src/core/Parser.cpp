#include "Parser.hpp"

#include "Operation.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

RequestData Parser::Parse( const std::string& jsonStr ) {
    auto j = json::parse( jsonStr );

    if ( !j.contains( "operation" ) ) {
        throw std::invalid_argument( "Missing operation" );
    }
    if ( !j.contains( "numA" ) ) {
        throw std::invalid_argument( "Missing numA" );
    }

    RequestData reqData;
    reqData.operation = j.at( "operation" ).get<EOperation>();
    reqData.numA = j.at( "numA" ).get<int32_t>();

    if ( j.contains( "numB" ) ) {
        reqData.numB = j.at( "numB" ).get<int32_t>();
    }

    return reqData;
}