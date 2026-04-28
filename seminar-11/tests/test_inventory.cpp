#include <catch2/catch_test_macros.hpp>

#include "../inc/inventory.hpp"
#include "../inc/item_factory.hpp"

#include <memory>
#include <string>
#include <type_traits>
#include <variant>

TEST_CASE("Inventory adds and removes items through expected results")
{
    inventory::Inventory bag(2);

    auto added = bag.addItem(
        0,
        std::make_unique<inventory::Equipment>("sword", 1.5, 2));
    REQUIRE(added.has_value());
    REQUIRE(bag.size() == 1);

    auto duplicate = bag.addItem(
        0,
        std::make_unique<inventory::Consumable>("potion", 0.2, 10));
    REQUIRE_FALSE(duplicate.has_value());
    REQUIRE(duplicate.error() == inventory::InventoryError::SlotOccupied);

    auto removed = bag.removeItem(0);
    REQUIRE(removed.has_value());
    REQUIRE(bag.size() == 0);

    auto empty = bag.removeItem(0);
    REQUIRE_FALSE(empty.has_value());
    REQUIRE(empty.error() == inventory::InventoryError::EmptySlot);
}

TEST_CASE("Inventory exposes occupied slots through optional references")
{
    inventory::Inventory bag(2);
    bag.addItemOrThrow(
        1,
        std::make_unique<inventory::Consumable>("potion", 0.2, 15));

    auto emptySlot = bag.getSlot(0);
    auto occupiedSlot = bag.getSlot(1);

    REQUIRE_FALSE(emptySlot.has_value());
    REQUIRE(occupiedSlot.has_value());
    REQUIRE(occupiedSlot->get().getId() == "potion");
}

TEST_CASE("Equipment use consumes durability and blocks broken items")
{
    inventory::Equipment sword("sword", 1.0, 2);

    REQUIRE(sword.use() == "Used equipment sword");
    REQUIRE(sword.getDurability() == 1);
    REQUIRE(sword.use() == "Used equipment sword");
    REQUIRE(sword.getDurability() == 0);
    REQUIRE_THROWS_AS(sword.use(), inventory::DurabilityZeroException);
    REQUIRE_THROWS_AS(sword.equip(), inventory::DurabilityZeroException);
}

TEST_CASE("Inventory validates empty slots and invalid equipment casts")
{
    inventory::Inventory bag(2);

    REQUIRE_THROWS_AS(bag.useSlot(0), inventory::EmptySlotException);

    bag.addItemOrThrow(
        0,
        std::make_unique<inventory::Consumable>("potion", 0.3, 20));
    REQUIRE_THROWS_AS(bag.equipSlot(0), inventory::InvalidItemTypeException);
}

TEST_CASE("ItemFactory returns variant and polymorphic clone")
{
    inventory::ItemVariant variant =
        inventory::ItemFactory::createEquipment("axe", 3.0, 4);

    bool visitedEquipment = false;
    std::visit(
        [&visitedEquipment](const auto& item) {
            using ItemType = std::decay_t<decltype(item)>;
            if constexpr (std::is_same_v<ItemType, inventory::Equipment>) {
                visitedEquipment = true;
                REQUIRE(item.getDurability() == 4);
            }
        },
        variant);

    auto item = inventory::ItemFactory::makePolymorphic(variant);
    REQUIRE(visitedEquipment);
    REQUIRE(item->getId() == "axe");
    REQUIRE(item->getWeight() == 3.0);
}

TEST_CASE("Throwing helpers convert expected errors to domain exceptions")
{
    inventory::Inventory bag(1);
    bag.addItemOrThrow(
        0,
        std::make_unique<inventory::Consumable>("potion", 0.2, 15));

    REQUIRE_THROWS_AS(
        bag.addItemOrThrow(
            0,
            std::make_unique<inventory::Equipment>("helmet", 1.0, 10)),
        inventory::SlotOccupiedException);
    REQUIRE_THROWS_AS(bag.removeItemOrThrow(2), std::out_of_range);
}

TEST_CASE("Adding to first free slot reports item limit when full")
{
    inventory::Inventory bag(1);

    REQUIRE(bag.addItem(
        std::make_unique<inventory::Consumable>("potion", 0.2, 15)));

    auto overflow = bag.addItem(
        std::make_unique<inventory::Equipment>("helmet", 1.0, 10));
    REQUIRE_FALSE(overflow.has_value());
    REQUIRE(overflow.error() == inventory::InventoryError::ItemLimitExceeded);
    REQUIRE_THROWS_AS(
        bag.addItemOrThrow(
            std::make_unique<inventory::Equipment>("helmet", 1.0, 10)),
        inventory::ItemLimitExceededException);
}
