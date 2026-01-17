#pragma once

#include <string>

enum class FunctionType {
    SIN,
    COS,
    EXP,
    UNKNOWN
};

struct ParseResult {
    FunctionType type;
    double value;
    bool success;
};

ParseResult parseFunction(const std::string& input);
double calculateFunction(FunctionType type, double x);
