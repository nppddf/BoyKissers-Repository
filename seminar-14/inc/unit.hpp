#ifndef SEMINAR_14_UNIT_HPP
#define SEMINAR_14_UNIT_HPP

#include <type_traits>

namespace Units {

struct LengthTag
{
};
struct MassTag
{
};

template <typename TDim> struct DimTraits;

template <> struct DimTraits<LengthTag>
{
    static constexpr double OTHER_TO_BASE = 0.3048;
    static constexpr double BASE_TO_OTHER = 1.0 / 0.3048;
};

template <> struct DimTraits<MassTag>
{
    static constexpr double OTHER_TO_BASE = 0.453592;
    static constexpr double BASE_TO_OTHER = 1.0 / 0.453592;
};

template <typename T>
concept AnyUnit = requires {
    typename T::DimTag;
    typename T::ValueType;
};

template <typename TValue, typename TDim> class Unit
{
    static_assert(std::is_arithmetic_v<TValue>,
                  "Unit value type must be arithmetic.");

public:
    using DimTag = TDim;
    using ValueType = TValue;

    static constexpr TValue TO_BASE = TValue(1);
    static constexpr TValue FROM_BASE = TValue(1);

    explicit constexpr Unit(TValue value): _value(value) {}

    constexpr TValue value() const { return _value; }

    constexpr TValue toBase() const { return _value * TO_BASE; }

    static constexpr Unit fromBase(TValue v) { return Unit(v * FROM_BASE); }

private:
    TValue _value;
};

template <typename TDim> class Unit<double, TDim>
{
public:
    using DimTag = TDim;
    using ValueType = double;

    static constexpr double TO_BASE = DimTraits<TDim>::OTHER_TO_BASE;
    static constexpr double FROM_BASE = DimTraits<TDim>::BASE_TO_OTHER;

    explicit constexpr Unit(double value): _value(value) {}

    constexpr double value() const { return _value; }

    constexpr double toBase() const { return _value * TO_BASE; }

    static constexpr Unit fromBase(double v) { return Unit(v * FROM_BASE); }

private:
    double _value;
};

template <> class Unit<double, LengthTag>
{
public:
    using DimTag = LengthTag;
    using ValueType = double;

    static constexpr double FEET_TO_METERS = 0.3048;
    static constexpr double METERS_TO_FEET = 1.0 / 0.3048;
    static constexpr double TO_BASE = FEET_TO_METERS;
    static constexpr double FROM_BASE = METERS_TO_FEET;

    explicit constexpr Unit(double value): _value(value) {}

    constexpr double value() const { return _value; }

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

template <> class Unit<double, MassTag>
{
public:
    using DimTag = MassTag;
    using ValueType = double;

    static constexpr double POUNDS_TO_KG = 0.453592;
    static constexpr double KG_TO_POUNDS = 1.0 / 0.453592;
    static constexpr double TO_BASE = POUNDS_TO_KG;
    static constexpr double FROM_BASE = KG_TO_POUNDS;

    explicit constexpr Unit(double value): _value(value) {}

    constexpr double value() const { return _value; }

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

template <AnyUnit UnitTarget, typename TValue, typename TDim>
constexpr auto convert(const Unit<TValue, TDim>& src) -> UnitTarget
{
    static_assert(
        std::is_same_v<TDim, typename UnitTarget::DimTag>,
        "Dimension mismatch: cannot convert between different physical "
        "dimensions.");
    auto baseValue = src.toBase();
    return UnitTarget::fromBase(
        static_cast<typename UnitTarget::ValueType>(baseValue));
}

using Feet = Unit<double, LengthTag>;
using Meters = Unit<float, LengthTag>;
using Pounds = Unit<double, MassTag>;
using Kilograms = Unit<float, MassTag>;

}  // namespace Units

#endif
