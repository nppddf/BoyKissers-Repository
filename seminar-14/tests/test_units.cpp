#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../inc/unit.hpp"

#include <type_traits>

TEST_CASE("Feet stores value in feet and converts to metres")
{
    constexpr Units::Feet feet(100.0);

    REQUIRE(feet.to_feet() == Catch::Approx(100.0));
    REQUIRE(feet.to_meters() == Catch::Approx(30.48));
    REQUIRE(feet.value() == Catch::Approx(100.0));
}

TEST_CASE("Feet full specialisation exposes constexpr conversion factors")
{
    static_assert(Units::Feet::FEET_TO_METERS == 0.3048);
    static_assert(Units::Feet::TO_BASE == 0.3048);
    SUCCEED("constexpr factors verified at compile time");
}

TEST_CASE("Feet toBase returns value in metres")
{
    constexpr Units::Feet feet(1.0);
    constexpr double base = feet.toBase();

    static_assert(base == 0.3048);
    REQUIRE(base == Catch::Approx(0.3048));
}

TEST_CASE("Feet fromBase creates unit from metres")
{
    constexpr auto feet = Units::Feet::fromBase(30.48);

    REQUIRE(feet.to_feet() == Catch::Approx(100.0).epsilon(1e-6));
}

TEST_CASE("Meters primary template stores SI value with factor 1")
{
    static_assert(Units::Meters::TO_BASE   == 1.0f);
    static_assert(Units::Meters::FROM_BASE == 1.0f);

    Units::Meters metres(30.48f);
    REQUIRE(static_cast<double>(metres.value()) == Catch::Approx(30.48).epsilon(1e-3));
    REQUIRE(static_cast<double>(metres.toBase()) == Catch::Approx(30.48).epsilon(1e-3));
}

TEST_CASE("Pounds stores value in pounds and converts to kg")
{
    constexpr Units::Pounds pounds(1.0);

    REQUIRE(pounds.to_pounds() == Catch::Approx(1.0));
    REQUIRE(pounds.to_kilograms() == Catch::Approx(0.453592).epsilon(1e-5));
    REQUIRE(pounds.value() == Catch::Approx(1.0));
}

TEST_CASE("Pounds full specialisation exposes constexpr conversion factors")
{
    static_assert(Units::Pounds::POUNDS_TO_KG == 0.453592);
    static_assert(Units::Pounds::TO_BASE == 0.453592);
    SUCCEED("constexpr mass factors verified at compile time");
}

TEST_CASE("Kilograms primary template stores SI value with factor 1")
{
    static_assert(Units::Kilograms::TO_BASE == 1.0f);

    Units::Kilograms kg(0.453592f);
    REQUIRE(static_cast<double>(kg.value()) == Catch::Approx(0.453592).epsilon(1e-4));
}

TEST_CASE("convert<Meters> from Feet gives correct SI value")
{
    constexpr Units::Feet feet(100.0);
    constexpr auto metres = Units::convert<Units::Meters>(feet);

    REQUIRE(static_cast<double>(metres.value()) == Catch::Approx(30.48).epsilon(1e-3));
}

TEST_CASE("convert<Feet> from Meters round-trips correctly")
{
    constexpr Units::Feet original(100.0);
    constexpr auto inMetres = Units::convert<Units::Meters>(original);
    const auto     backFeet = Units::convert<Units::Feet>(inMetres);

    REQUIRE(backFeet.to_feet() == Catch::Approx(100.0).epsilon(1e-3));
}

TEST_CASE("convert<Kilograms> from Pounds gives correct SI value")
{
    Units::Pounds pounds(10.0);
    auto          kg = Units::convert<Units::Kilograms>(pounds);

    REQUIRE(static_cast<double>(kg.value()) == Catch::Approx(4.53592).epsilon(1e-4));
}

TEST_CASE("convert<Pounds> from Kilograms round-trips correctly")
{
    Units::Pounds original(10.0);
    auto          inKg      = Units::convert<Units::Kilograms>(original);
    auto          backPounds = Units::convert<Units::Pounds>(inKg);

    REQUIRE(backPounds.to_pounds() == Catch::Approx(10.0).epsilon(1e-3));
}

TEST_CASE("DimTag aliases are correct for each specialisation")
{
    static_assert(std::is_same_v<Units::Feet::DimTag,      Units::LengthTag>);
    static_assert(std::is_same_v<Units::Meters::DimTag,    Units::LengthTag>);
    static_assert(std::is_same_v<Units::Pounds::DimTag,    Units::MassTag>);
    static_assert(std::is_same_v<Units::Kilograms::DimTag, Units::MassTag>);
    SUCCEED("All DimTag aliases verified at compile time");
}

TEST_CASE("Entire conversion pipeline evaluates at compile time")
{
    constexpr Units::Feet  feet(100.0);
    constexpr double       metres = feet.to_meters();

    static_assert(metres > 30.0 && metres < 31.0,
                  "compile-time metres value out of expected range");
    REQUIRE(metres == Catch::Approx(30.48));
}

TEST_CASE("convert is constexpr: result usable in static_assert")
{
    constexpr auto metres = Units::convert<Units::Meters>(Units::Feet(1.0));

    static_assert(metres.value() > 0.30f && metres.value() < 0.31f);
    SUCCEED("constexpr convert verified");
}

TEST_CASE("DimTraits provides correct factors for LengthTag")
{
    static_assert(Units::DimTraits<Units::LengthTag>::OTHER_TO_BASE == 0.3048);
    static_assert(Units::DimTraits<Units::MassTag>::OTHER_TO_BASE   == 0.453592);
    SUCCEED("DimTraits factors verified at compile time");
}
