#pragma once

#include <libpq-fe.h>

#include <iostream>
#include <memory>

namespace pg {

class Connection {
public:
    Connection( const std::string& connectInfo );

    PGconn* Get() {
        return pgConnDb.get();
    }

    Connection( const Connection& ) = delete;
    Connection& operator=( const Connection& ) = delete;

private:
    struct PGconnDeleter {
        void operator()( PGconn* conn ) const {
            if ( conn ) {
                PQfinish( conn );
            }
        }
    };

    using PgConnectionPtr = std::unique_ptr<PGconn, PGconnDeleter>;

    std::unique_ptr<PGconn, PGconnDeleter> pgConnDb;
};

};  // namespace pg
