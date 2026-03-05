#pragma ocne

#include <SimpleMath.hpp>

#include "RequestData.hpp"

class Calculator {
public:
    int32_t Calculate( const RequestData& requestData );

private:
    mathlib::SimpleMath math{};
};
