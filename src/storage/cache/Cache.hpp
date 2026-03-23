#pragma once

#include <unordered_map>

#include "storage/Data.hpp"

namespace calculator {

struct Cache {
    std::unordered_map<OperationKey, ResultOperation, OperationKeyHash> data;
};

}  // namespace calculator
