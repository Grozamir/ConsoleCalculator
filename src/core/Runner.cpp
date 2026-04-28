#include "Runner.hpp"

#include "Logger.hpp"

namespace calculator {

void Runner::Init() {
    storage.Init();
    storage.WarmUpCache();
}

Response Runner::Run( const std::string& inputJsonStr ) {
    try {
        auto requestData = parser.Parse( inputJsonStr );
        checker.Validate( requestData );

        auto operationKey = OperationKey::MakeFromRequestData( requestData );

        int32_t result = 0;

        if ( auto resultOpt = storage.FindResult( operationKey ); resultOpt.has_value() ) {
            if ( resultOpt.value().status == 0 ) {
                result = resultOpt.value().calculateResult;
            } else {
                throw std::logic_error( mathlib::MathErrorCodeToString( static_cast<mathlib::MathErrorCode>( resultOpt.value().status ) ) );
            }
        } else {
            try {
                result = calculator.Calculate( requestData );
                storage.AddCalculatorResult( operationKey, result );
            } catch ( const mathlib::MathException& mathEx ) {
                const int32_t status = mathEx.GetErrorCode();
                storage.AddFailCalculatorResult( operationKey, status );
                Logger::Instance().Error( mathEx.what() );
                return Response::Error( mathEx.what() );
            } catch ( const std::exception& ex ) {
                Logger::Instance().Error( ex.what() );
                return Response::Error( ex.what() );
            }
        }

        printer.PrintResult( result );

        return Response::Ok( result );
    } catch ( const std::exception& ex ) {
        Logger::Instance().Error( ex.what() );
        return Response::Error( ex.what() );
    }
}

}  // namespace calculator