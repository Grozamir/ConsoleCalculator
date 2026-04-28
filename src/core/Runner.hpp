#pragma once

#include "Calculator.hpp"
#include "Checker.hpp"
#include "Operation.hpp"
#include "Parser.hpp"
#include "Printer.hpp"
#include "Response.hpp"

#include "storage/Storage.hpp"

namespace calculator {

class Runner {
public:
    void Init();
    Response Run( const std::string& inputJsonStr );

private:
    Parser parser{};
    Checker checker{};
    Calculator calculator{};
    Printer printer{};

    Storage storage{};
};

}  // namespace calculator