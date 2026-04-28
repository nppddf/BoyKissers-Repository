#pragma once

#include "inventory.hpp"

#include <memory>
#include <string_view>
#include <variant>

namespace inventory {

using ItemVariant = std::variant<Equipment, Consumable>;

class ItemFactory {
public:
    static ItemVariant createEquipment(std::string_view name,
                                       double weight,
                                       int durability);
    static ItemVariant createConsumable(std::string_view name,
                                        double weight,
                                        int healPower);
    static std::unique_ptr<Item> makePolymorphic(const ItemVariant& item);
};

} // namespace inventory
