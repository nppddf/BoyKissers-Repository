#include <catch2/catch_test_macros.hpp>

#include "name_utils.h"

TEST_CASE("splitFio splits into three words")
{
    const auto parts = name_utils::splitFio(L"Smith John Junior");
    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == L"Smith");
    REQUIRE(parts[1] == L"John");
    REQUIRE(parts[2] == L"Junior");
}

TEST_CASE("splitFio ignores extra spaces")
{
    const auto parts = name_utils::splitFio(L"  Smith   John   Junior  ");
    REQUIRE(parts.size() == 3);
    REQUIRE(parts[0] == L"Smith");
    REQUIRE(parts[1] == L"John");
    REQUIRE(parts[2] == L"Junior");
}

TEST_CASE("splitFio throws if not exactly three words")
{
    REQUIRE_THROWS_AS(name_utils::splitFio(L"Smith John"), std::runtime_error);
    REQUIRE_THROWS_AS(name_utils::splitFio(L"Smith John Junior Extra"), std::runtime_error);
    REQUIRE_THROWS_AS(name_utils::splitFio(L""), std::runtime_error);
}

TEST_CASE("isValidFioCharacters accepts letters and spaces")
{
    REQUIRE(name_utils::isValidFioCharacters(L"Smith John Junior"));
    REQUIRE(name_utils::isValidFioCharacters(L"  Smith   John  "));
}

TEST_CASE("isValidFioCharacters rejects digits and punctuation")
{
    REQUIRE_FALSE(name_utils::isValidFioCharacters(L"Smith2 John Junior"));
    REQUIRE_FALSE(name_utils::isValidFioCharacters(L"Smith John-Junior"));
    REQUIRE_FALSE(name_utils::isValidFioCharacters(L"Smith John."));
}

TEST_CASE("toUpper uppercases letters")
{
    REQUIRE(name_utils::toUpper(L"Abc XyZ") == L"ABC XYZ");
}

TEST_CASE("capitalizeWords capitalizes each word")
{
    REQUIRE(name_utils::capitalizeWords(L"SMITH john jUnIoR") == L"Smith John Junior");
    REQUIRE(name_utils::capitalizeWords(L"  sMiTh   jOhN  jUnIoR  ") == L"Smith John Junior");
}

TEST_CASE("formatShortFio formats surname and initials")
{
    REQUIRE(name_utils::formatShortFio(L"SMITH", L"john", L"junior") == L"Smith J. J.");
    REQUIRE(name_utils::formatShortFio(L"SMITH", L"john", L"") == L"Smith J. ");
    REQUIRE(name_utils::formatShortFio(L"SMITH", L"", L"junior") == L"Smith J.");
}
