#include "function_parser.h"
#include <cmath>
#include <regex>
#include <stdexcept>

ParseResult parseFunction(const std::string& input)
{
    ParseResult result;
    result.success = false;
    result.type = FunctionType::UNKNOWN;
    
    std::regex sinPattern(R"(sin\s*\(\s*([+-]?[\d.]+)\s*\))", std::regex::icase);
    
    std::regex cosPattern(R"(cos\s*\(\s*([+-]?[\d.]+)\s*\))", std::regex::icase);
    
    std::regex expPattern(R"(e\s*\^\s*\(?\s*([+-]?[\d.]+)\s*\)?)", std::regex::icase);

    std::smatch match;

    if (std::regex_match(input, match, sinPattern)) {
        result.type = FunctionType::SIN;
        result.success = true;
        try {
            result.value = std::stod(match[1].str());
        } catch (...) {
            result.success = false;
        }
    } else if (std::regex_match(input, match, cosPattern)) {
        result.type = FunctionType::COS;
        result.success = true;
        try {
            result.value = std::stod(match[1].str());
        } catch (...) {
            result.success = false;
        }
    } else if (std::regex_match(input, match, expPattern)) {
        result.type = FunctionType::EXP;
        result.success = true;
        try {
            result.value = std::stod(match[1].str());
        } catch (...) {
            result.success = false;
        }
    }

    return result;
}

double calculateFunction(FunctionType type, double x)
{
    switch (type) {
    case FunctionType::SIN:
        return std::sin(x);
    case FunctionType::COS:
        return std::cos(x);
    case FunctionType::EXP:
        return std::exp(x);
    default:
        return 0.0;
    }
}
