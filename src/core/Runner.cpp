#include "Runner.hpp"

#include "Logger.hpp"

namespace calculator {

void Runner::Run( const std::string& inputJsonStr ) {
    try {
        auto requestData = parser.Parse( inputJsonStr );

        checker.Validate( requestData );
        auto result = calculator.Calculate( requestData );

        printer.PrintResult( result );
    } catch ( const std::exception& ex ) {
        Logger::Instance().Error( ex.what() );
    }
}

}  // namespace calculator