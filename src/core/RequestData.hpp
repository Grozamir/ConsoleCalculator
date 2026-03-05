#pragma once

#include "Operation.hpp"

struct RequestData {
    EOperation operation = EOperation::none;
    int32_t numA = 0;
    std::optional<int32_t> numB = std::nullopt;
};
