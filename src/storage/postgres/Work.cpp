#include "Work.hpp"

namespace pg {

PGresultPtr Work::Exec( const std::string& command ) {
    auto* res = PQexec( connDb->Get(), command.c_str() );
    return std::unique_ptr<PGresult, PGresultDeleter>( res );
}

PGresultPtr Work::ExecParams( const std::string& command, const std::vector<std::string>& params ) {
    std::vector<const char*> normParams;
    normParams.reserve( params.capacity() );

    for ( auto& param : params ) {
        normParams.push_back( param.c_str() );
    }

    auto* res = PQexecParams(
        connDb->Get(),
        command.c_str(),
        normParams.size(),
        nullptr,
        normParams.data(),
        nullptr,
        nullptr,
        0 );

    return std::unique_ptr<PGresult, PGresultDeleter>( res );
}

}  // namespace pg
