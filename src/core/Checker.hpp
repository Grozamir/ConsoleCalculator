#pragma once

#include "RequestData.hpp"

namespace calculator {

class Checker {
public:
    void Validate( const RequestData& requestData );
};

}  // namespace calculator
