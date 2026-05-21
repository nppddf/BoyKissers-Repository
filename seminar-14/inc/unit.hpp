#ifndef SEMINAR_14_UNIT_HPP
#define SEMINAR_14_UNIT_HPP

#include <type_traits>

namespace Units {

// ── Dimension tags ─────────────────────────────────────────────────────────

struct LengthTag {};
struct MassTag {};

// ── Conversion traits: "other" unit ↔ SI base ──────────────────────────────
// Intentionally undefined for unknown dimensions → compile error on access.

template<typename TDim>
struct DimTraits;

template<>
struct DimTraits<LengthTag>
{
    static constexpr double OTHER_TO_BASE = 0.3048;          // feet → metres
    static constexpr double BASE_TO_OTHER = 1.0 / 0.3048;   // metres → feet
};

template<>
struct DimTraits<MassTag>
{
    static constexpr double OTHER_TO_BASE = 0.453592;        // pounds → kg
    static constexpr double BASE_TO_OTHER = 1.0 / 0.453592; // kg → pounds
};

// ── C++20 concept: any Unit-shaped type ────────────────────────────────────

template<typename T>
concept AnyUnit = requires {
    typename T::DimTag;
    typename T::ValueType;
};

// ── Primary template Unit<TValue, TDim> ────────────────────────────────────
// Stores value in SI base units (metres for Length, kg for Mass).
// e.g. Unit<float, LengthTag> stores metres; Unit<float, MassTag> stores kg.

template<typename TValue, typename TDim>
class Unit
{
    static_assert(std::is_arithmetic_v<TValue>,
                  "Unit value type must be arithmetic.");

public:
    using DimTag   = TDim;
    using ValueType = TValue;

    // Already in base units → conversion factor is 1
    static constexpr TValue TO_BASE   = TValue(1);
    static constexpr TValue FROM_BASE = TValue(1);

    explicit constexpr Unit(TValue value) : _value(value) {}

    constexpr TValue value() const { return _value; }

    // Returns value in SI base units
    constexpr TValue toBase() const { return _value * TO_BASE; }

    static constexpr Unit fromBase(TValue v) { return Unit(v * FROM_BASE); }

private:
    TValue _value;
};

// ── Partial specialisation Unit<double, TDim> ──────────────────────────────
// Stores value in "other" (non-SI) units with constexpr conversion factors
// derived from DimTraits<TDim>.
// Applies to any TDim whose full specialisation below does NOT override it.

template<typename TDim>
class Unit<double, TDim>
{
public:
    using DimTag   = TDim;
    using ValueType = double;

    static constexpr double TO_BASE   = DimTraits<TDim>::OTHER_TO_BASE;
    static constexpr double FROM_BASE = DimTraits<TDim>::BASE_TO_OTHER;

    explicit constexpr Unit(double value) : _value(value) {}

    constexpr double value() const { return _value; }

    constexpr double toBase() const { return _value * TO_BASE; }

    static constexpr Unit fromBase(double v) { return Unit(v * FROM_BASE); }

private:
    double _value;
};

// ── Full specialisation Unit<double, LengthTag> ────────────────────────────
// Stores value in feet; overrides the partial spec.
// Adds to_meters() and to_feet() methods.

template<>
class Unit<double, LengthTag>
{
public:
    using DimTag   = LengthTag;
    using ValueType = double;

    static constexpr double FEET_TO_METERS = 0.3048;
    static constexpr double METERS_TO_FEET = 1.0 / 0.3048;
    static constexpr double TO_BASE        = FEET_TO_METERS;
    static constexpr double FROM_BASE      = METERS_TO_FEET;

    explicit constexpr Unit(double value) : _value(value) {}

    constexpr double value() const { return _value; }     // value in feet

    constexpr double toBase() const { return _value * FEET_TO_METERS; }

    static constexpr Unit fromBase(double metres)
    {
        return Unit(metres * METERS_TO_FEET);
    }

    constexpr double to_feet() const { return _value; }
    constexpr double to_meters() const { return _value * FEET_TO_METERS; }

private:
    double _value;
};

// ── Full specialisation Unit<double, MassTag> ──────────────────────────────
// Stores value in pounds; overrides the partial spec.
// Adds to_kilograms() and to_pounds() methods.

template<>
class Unit<double, MassTag>
{
public:
    using DimTag   = MassTag;
    using ValueType = double;

    static constexpr double POUNDS_TO_KG = 0.453592;
    static constexpr double KG_TO_POUNDS = 1.0 / 0.453592;
    static constexpr double TO_BASE      = POUNDS_TO_KG;
    static constexpr double FROM_BASE    = KG_TO_POUNDS;

    explicit constexpr Unit(double value) : _value(value) {}

    constexpr double value() const { return _value; }     // value in pounds

    constexpr double toBase() const { return _value * POUNDS_TO_KG; }

    static constexpr Unit fromBase(double kg)
    {
        return Unit(kg * KG_TO_POUNDS);
    }

    constexpr double to_kilograms() const { return _value * POUNDS_TO_KG; }
    constexpr double to_pounds() const { return _value; }

private:
    double _value;
};

// ── convert<UnitTarget>(src) ───────────────────────────────────────────────
// Converts src to UnitTarget through SI base.
// Requires matching DimTag — mismatched dimensions are blocked at compile time.

template<AnyUnit UnitTarget, typename TValue, typename TDim>
constexpr auto convert(const Unit<TValue, TDim>& src) -> UnitTarget
{
    static_assert(
        std::is_same_v<TDim, typename UnitTarget::DimTag>,
        "Dimension mismatch: cannot convert between different physical "
        "dimensions.");
    auto baseValue = src.toBase();  // auto preserves precision of src's type
    return UnitTarget::fromBase(
        static_cast<typename UnitTarget::ValueType>(baseValue));
}

// ── Convenient type aliases ────────────────────────────────────────────────

using Feet      = Unit<double, LengthTag>;  // full spec → to_feet/to_meters
using Meters    = Unit<float,  LengthTag>;  // primary template → SI metres
using Pounds    = Unit<double, MassTag>;    // full spec → to_pounds/to_kilograms
using Kilograms = Unit<float,  MassTag>;    // primary template → SI kg

}  // namespace Units

#endif  // SEMINAR_14_UNIT_HPP
