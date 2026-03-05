#pragma once

#include <nlohmann/json.hpp>

enum class EOperation : uint8_t {
    none,
    add,
    sub,
    mul,
    div,
    pow,
    factorial,
};

NLOHMANN_JSON_SERIALIZE_ENUM(
    EOperation,
    {
        { EOperation::none, nullptr },
        { EOperation::add, "add" },
        { EOperation::sub, "sub" },
        { EOperation::mul, "mul" },
        { EOperation::div, "div" },
        { EOperation::pow, "mpowl" },
        { EOperation::factorial, "factorial" },
    } )