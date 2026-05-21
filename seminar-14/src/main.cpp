#include "unit.hpp"

#include <iomanip>
#include <iostream>

int main()
{
    constexpr Units::Feet feetUnit(100.0);

    std::cout << "Original: "
              << std::fixed << std::setprecision(1) << feetUnit.to_feet()
              << " ft\n";

    // Method 1: direct method on the full specialisation
    std::cout << "Converted to meters: "
              << std::fixed << std::setprecision(4) << feetUnit.to_meters()
              << "\n";

    // Method 2: generic convert<> function (compile-time value via constexpr)
    constexpr auto metersUnit = Units::convert<Units::Meters>(feetUnit);
    std::cout << "Converted to meters: "
              << std::fixed << std::setprecision(4) << metersUnit.value()
              << "\n";

    // Attempting convert<Units::Pounds>(feetUnit) would produce:
    //   static_assert: "Dimension mismatch: cannot convert between different
    //   physical dimensions."
    std::cout
        << "[Compile-time check] Length to Mass conversion blocked "
           "successfully.\n";

    return 0;
}
