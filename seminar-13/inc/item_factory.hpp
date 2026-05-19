#ifndef SEMINAR_13_ITEM_FACTORY_HPP
#define SEMINAR_13_ITEM_FACTORY_HPP

#include "inventory.hpp"

#include <memory>
#include <string_view>

namespace GameInventory {

class ItemFactory
{
public:
    static std::unique_ptr<Item> createWeapon(std::string_view name,
                                               double weight,
                                               int damage);
    static std::unique_ptr<Item> createArmor(std::string_view name,
                                              double weight,
                                              int defense);
};

}  // namespace GameInventory

#endif  // SEMINAR_13_ITEM_FACTORY_HPP
