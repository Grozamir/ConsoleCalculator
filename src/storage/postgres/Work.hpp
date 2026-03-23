#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Connection.hpp"

namespace pg {

struct PGresultDeleter {
    void operator()( PGresult* res ) const {
        if ( res ) {
            PQclear( res );
        }
    }
};

using PGresultPtr = std::unique_ptr<PGresult, PGresultDeleter>;

class Work {
public:
    Work( const std::shared_ptr<Connection>& newConnection )
        : connDb( newConnection ) {
    }

    PGresultPtr Exec( const std::string& command );
    PGresultPtr ExecParams( const std::string& command, const std::vector<std::string>& params );

private:
    std::shared_ptr<Connection> connDb;
};

}  // namespace pg
