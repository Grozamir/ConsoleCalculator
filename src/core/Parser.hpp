#pragma once

#include "RequestData.hpp"

namespace calculator {

class Parser {
public:
    RequestData Parse( const std::string& jsonStr );
};

}  // namespace calculator
