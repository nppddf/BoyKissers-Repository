#include "inventory.hpp"
#include "item_factory.hpp"

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

namespace {

void printExpectedResult(const std::expected<bool, inventory::InventoryError>& result)
{
    if (result) {
        std::cout << "Operation completed\n";
        return;
    }

    std::cout << "Operation failed: " << inventory::toString(result.error())
              << '\n';
}

} // namespace

int main()
{
    inventory::Inventory bag(10);

    std::vector<inventory::ItemVariant> createdItems = {
        inventory::ItemFactory::createEquipment("iron_sword", 5.0, 3),
        inventory::ItemFactory::createConsumable("small_potion", 0.4, 25),
        inventory::ItemFactory::createEquipment("broken_shield", 7.0, 0),
    };

    for (const auto& item : createdItems) {
        std::visit(
            [](const auto& concreteItem) {
                std::cout << "Factory created: " << concreteItem.getId()
                          << '\n';
            },
            item);
    }

    bag.addItemOrThrow(0, inventory::ItemFactory::makePolymorphic(createdItems[0]));
    bag.addItemOrThrow(1, inventory::ItemFactory::makePolymorphic(createdItems[1]));
    bag.addItemOrThrow(2, inventory::ItemFactory::makePolymorphic(createdItems[2]));

    if (auto slot = bag.getSlot(0)) {
        std::cout << "Slot 0 contains: " << slot->get().getId() << '\n';
    }

    std::cout << bag.equipSlot(0) << '\n';
    std::cout << bag.useSlot(1) << '\n';

    try {
        std::cout << bag.useSlot(2) << '\n';
    } catch (const inventory::DurabilityZeroException& error) {
        std::cout << "Handled durability error: " << error.what() << '\n';
    }

    try {
        std::cout << bag.equipSlot(1) << '\n';
    } catch (const inventory::InvalidItemTypeException& error) {
        std::cout << "Handled type error: " << error.what() << '\n';
    }

    printExpectedResult(bag.addItem(
        0,
        std::make_unique<inventory::Consumable>("another_potion", 0.3, 10)));

    for (std::size_t slot = 3; slot < bag.capacity(); ++slot) {
        bag.addItemOrThrow(
            slot,
            std::make_unique<inventory::Consumable>("ration", 0.2, 5));
    }

    printExpectedResult(bag.addItem(
        std::make_unique<inventory::Equipment>("spare_axe", 2.0, 4)));

    try {
        bag.addItemOrThrow(
            std::make_unique<inventory::Consumable>("extra_ration", 0.2, 5));
    } catch (const inventory::ItemLimitExceededException& error) {
        std::cout << "Handled limit error: " << error.what() << '\n';
    }

    return 0;
}
