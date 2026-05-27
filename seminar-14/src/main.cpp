#include "unit.hpp"

#include <iomanip>
#include <iostream>

int main()
{
    constexpr Units::Feet feetUnit(100.0);

    std::cout << "Original: " << std::fixed << std::setprecision(1)
              << feetUnit.to_feet() << " ft\n";

    std::cout << "Converted to meters: " << std::fixed << std::setprecision(4)
              << feetUnit.to_meters() << "\n";

    constexpr auto metersUnit = Units::convert<Units::Meters>(feetUnit);
    std::cout << "Converted to meters: " << std::fixed << std::setprecision(4)
              << metersUnit.value() << "\n";

    std::cout << "[Compile-time check] Length to Mass conversion blocked "
                 "successfully.\n";

    return 0;
}
