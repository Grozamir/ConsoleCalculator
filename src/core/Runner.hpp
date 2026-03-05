#pragma once

#include "Calculator.hpp"
#include "Checker.hpp"
#include "Operation.hpp"
#include "Parser.hpp"
#include "Printer.hpp"

class Runner {
public:
    void Run( const std::string& inputJsonStr );

private:
    Parser parser{};
    Checker checker{};
    Calculator calculator{};
    Printer printer{};
};