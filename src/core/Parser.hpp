#pragma once

#include "RequestData.hpp"

class Parser {
public:
    RequestData Parse( const std::string& jsonStr );
};
