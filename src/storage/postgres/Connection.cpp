#include "Connection.hpp"

namespace pg {
Connection::Connection( const std::string& connectInfo ) {
    auto* tempConn = PQconnectdb( connectInfo.c_str() );

    if ( !tempConn ) {
        throw std::runtime_error( "PQconnectdb failed" );
    }

    if ( PQstatus( tempConn ) != CONNECTION_OK ) {
        const std::string err = PQerrorMessage( tempConn );

        PQfinish( tempConn );

        throw std::runtime_error( err );
    }

    pgConnDb = PgConnectionPtr( tempConn );
}

}  // namespace pg