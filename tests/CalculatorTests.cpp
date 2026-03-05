#include "../src/core/Calculator.hpp"
#include "../src/core/Checker.hpp"
#include "../src/core/Parser.hpp"

#include <gtest/gtest.h>

TEST( CalculatorTest, Add ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 5;
    reqData.numB = 3;
    reqData.operation = EOperation::add;

    EXPECT_EQ( calc.Calculate( reqData ), 8 );
}

TEST( CalculatorTest, Sub ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 5;
    reqData.numB = 3;
    reqData.operation = EOperation::sub;

    EXPECT_EQ( calc.Calculate( reqData ), 2 );
}

TEST( CalculatorTest, Mul ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 5;
    reqData.numB = 3;
    reqData.operation = EOperation::mul;

    EXPECT_EQ( calc.Calculate( reqData ), 15 );
}

TEST( CalculatorTest, Div ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 10;
    reqData.numB = 5;
    reqData.operation = EOperation::div;

    EXPECT_EQ( calc.Calculate( reqData ), 2 );
}

TEST( CalculatorTest, Pow ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 2;
    reqData.numB = 10;
    reqData.operation = EOperation::pow;

    EXPECT_EQ( calc.Calculate( reqData ), 1024 );
}

TEST( CalculatorTest, Factorial ) {
    Calculator calc;

    RequestData reqData;
    reqData.numA = 5;
    reqData.operation = EOperation::factorial;

    EXPECT_EQ( calc.Calculate( reqData ), 120 );
}

TEST( CalculatorTest, Parser ) {
    Parser parser;

    std::string str = R"({"numA":1,"numB":123,"operation":"mul"})";
    auto reqData = parser.Parse( str );

    EXPECT_EQ( reqData.numA, 1 );
    EXPECT_EQ( reqData.numB, 123 );
    EXPECT_EQ( reqData.operation, EOperation::mul );
}

TEST( CheckerTest, FactorialNegativeThrows ) {
    Checker checker;

    RequestData req;
    req.operation = EOperation::factorial;
    req.numA = -1;

    EXPECT_THROW( checker.Validate( req ), std::logic_error );
}