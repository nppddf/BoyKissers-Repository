#include "item_factory.hpp"

namespace GameInventory {

std::unique_ptr<Item>
ItemFactory::createWeapon(std::string_view name, double weight, int damage)
{
    return std::make_unique<Weapon>(name, weight, damage);
}

std::unique_ptr<Item>
ItemFactory::createArmor(std::string_view name, double weight, int defense)
{
    return std::make_unique<Armor>(name, weight, defense);
}

}  // namespace GameInventory
