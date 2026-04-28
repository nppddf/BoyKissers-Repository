#include "item_factory.hpp"

#include <variant>

namespace inventory {

ItemVariant ItemFactory::createEquipment(std::string_view name,
                                         double weight,
                                         int durability)
{
    return Equipment(name, weight, durability);
}

ItemVariant ItemFactory::createConsumable(std::string_view name,
                                          double weight,
                                          int healPower)
{
    return Consumable(name, weight, healPower);
}

std::unique_ptr<Item> ItemFactory::makePolymorphic(const ItemVariant& item)
{
    return std::visit(
        [](const auto& concreteItem) -> std::unique_ptr<Item> {
            return concreteItem.clone();
        },
        item);
}

} // namespace inventory
