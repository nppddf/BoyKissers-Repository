#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "function_parser.h"

TEST_CASE("parse sin function") {
    ParseResult result = parseFunction("sin(0)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::SIN);
    REQUIRE(result.value == 0.0);
    
    result = parseFunction("sin(1.5)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::SIN);
    REQUIRE(result.value == 1.5);
    
    result = parseFunction("sin(-3.14)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::SIN);
    REQUIRE(result.value == -3.14);
    
    result = parseFunction("SIN(2)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::SIN);
}

TEST_CASE("parse cos function") {
    ParseResult result = parseFunction("cos(0)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::COS);
    REQUIRE(result.value == 0.0);
    
    result = parseFunction("cos(2.5)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::COS);
    REQUIRE(result.value == 2.5);
    
    result = parseFunction("cos(-1.0)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::COS);
    REQUIRE(result.value == -1.0);
}

TEST_CASE("parse exp function") {
    ParseResult result = parseFunction("e^(0)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::EXP);
    REQUIRE(result.value == 0.0);
    
    result = parseFunction("e^1");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::EXP);
    REQUIRE(result.value == 1.0);
    
    result = parseFunction("e^(-2.5)");
    REQUIRE(result.success == true);
    REQUIRE(result.type == FunctionType::EXP);
    REQUIRE(result.value == -2.5);
}

TEST_CASE("parse invalid input") {
    ParseResult result = parseFunction("invalid");
    REQUIRE(result.success == false);
    REQUIRE(result.type == FunctionType::UNKNOWN);
    
    result = parseFunction("sinx");
    REQUIRE(result.success == false);
    
    result = parseFunction("cos");
    REQUIRE(result.success == false);
    
    result = parseFunction("");
    REQUIRE(result.success == false);
}

TEST_CASE("calculate sin function") {
    double result = calculateFunction(FunctionType::SIN, 0.0);
    REQUIRE(result == 0.0);
    
    result = calculateFunction(FunctionType::SIN, M_PI / 2);
    REQUIRE(std::abs(result - 1.0) < 1e-9);
    
    result = calculateFunction(FunctionType::SIN, M_PI);
    REQUIRE(std::abs(result) < 1e-9);
}

TEST_CASE("calculate cos function") {
    double result = calculateFunction(FunctionType::COS, 0.0);
    REQUIRE(std::abs(result - 1.0) < 1e-9);
    
    result = calculateFunction(FunctionType::COS, M_PI / 2);
    REQUIRE(std::abs(result) < 1e-9);
    
    result = calculateFunction(FunctionType::COS, M_PI);
    REQUIRE(std::abs(result + 1.0) < 1e-9);
}

TEST_CASE("calculate exp function") {
    double result = calculateFunction(FunctionType::EXP, 0.0);
    REQUIRE(std::abs(result - 1.0) < 1e-9);
    
    result = calculateFunction(FunctionType::EXP, 1.0);
    REQUIRE(std::abs(result - M_E) < 1e-9);
    
    result = calculateFunction(FunctionType::EXP, -1.0);
    REQUIRE(std::abs(result - 1.0 / M_E) < 1e-9);
}

TEST_CASE("calculate unknown function") {
    double result = calculateFunction(FunctionType::UNKNOWN, 5.0);
    REQUIRE(result == 0.0);
}
