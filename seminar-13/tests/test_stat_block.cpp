#include <catch2/catch_test_macros.hpp>

#include "../inc/inventory.hpp"
#include "../inc/item_factory.hpp"

#include <memory>
#include <type_traits>

TEST_CASE("StatBlock deep copy leaves original unchanged")
{
    GameInventory::StatBlock original(3);
    original[0] = 10.0f;
    original[1] = 20.0f;
    original[2] = 30.0f;

    auto copy = original;
    copy[0] = 99.0f;

    REQUIRE(original[0] == 10.0f);
    REQUIRE(copy[0] == 99.0f);
    REQUIRE(original.size() == 3);
    REQUIRE(copy.size() == 3);
}

TEST_CASE("StatBlock move transfers data and clears source size")
{
    GameInventory::StatBlock source(3);
    source[0] = 5.0f;
    source[1] = 15.0f;

    auto dest = std::move(source);

    REQUIRE(dest[0] == 5.0f);
    REQUIRE(dest[1] == 15.0f);
    REQUIRE(dest.size() == 3);
    REQUIRE(source.size() == 0);
}

TEST_CASE("StatBlock copy assignment is deep and independent")
{
    GameInventory::StatBlock block1(2);
    block1[0] = 1.0f;
    block1[1] = 2.0f;

    GameInventory::StatBlock block2(1);
    block2 = block1;
    block2[0] = 99.0f;

    REQUIRE(block1[0] == 1.0f);
    REQUIRE(block2[0] == 99.0f);
    REQUIRE(block2.size() == 2);
}

TEST_CASE("StatBlock move assignment transfers data and clears source")
{
    GameInventory::StatBlock source(2);
    source[0] = 7.0f;

    GameInventory::StatBlock dest(1);
    dest = std::move(source);

    REQUIRE(dest[0] == 7.0f);
    REQUIRE(dest.size() == 2);
    REQUIRE(source.size() == 0);
}

TEST_CASE("Weapon and Armor polymorphic equip")
{
    GameInventory::Weapon sword("Sword", 5.0, 15);
    GameInventory::Armor chainmail("Chainmail", 8.0, 10);

    REQUIRE(sword.getDamage() == 15);
    REQUIRE(chainmail.getDefense() == 10);
    REQUIRE(sword.equip() == "Equipped Sword (dmg=15)");
    REQUIRE(chainmail.equip() == "Wearing Chainmail (def=10)");
}

TEST_CASE("Inventory adds items and throws on overflow")
{
    GameInventory::Inventory bag(2);
    REQUIRE(bag.size() == 0);
    REQUIRE(bag.capacity() == 2);

    bag.addItemOrThrow(
        std::make_unique<GameInventory::Weapon>("Axe", 3.0, 20));
    REQUIRE(bag.size() == 1);

    bag.addItemOrThrow(
        std::make_unique<GameInventory::Armor>("Shield", 4.0, 8));
    REQUIRE(bag.size() == 2);

    REQUIRE_THROWS_AS(
        bag.addItemOrThrow(
            std::make_unique<GameInventory::Weapon>("Bow", 2.0, 12)),
        GameInventory::ItemLimitExceededException);
}

TEST_CASE("Inventory getSlot returns nullopt for empty slots")
{
    GameInventory::Inventory bag(3);
    bag.addItemOrThrow(
        std::make_unique<GameInventory::Weapon>("Sword", 1.0, 10));

    REQUIRE(bag.getSlot(0).has_value());
    REQUIRE_FALSE(bag.getSlot(1).has_value());
    REQUIRE(bag.getSlot(0)->get().getName() == "Sword");
}

TEST_CASE("Inventory equipSlot throws on empty slot")
{
    GameInventory::Inventory bag(2);
    REQUIRE_THROWS_AS(bag.equipSlot(0), GameInventory::EmptySlotException);
}

TEST_CASE("Inventory removeItemOrThrow clears slot")
{
    GameInventory::Inventory bag(2);
    bag.addItemOrThrow(
        std::make_unique<GameInventory::Armor>("Shield", 4.0, 5));
    bag.removeItemOrThrow(0);

    REQUIRE(bag.size() == 0);
    REQUIRE_FALSE(bag.getSlot(0).has_value());
}

TEST_CASE("Inventory is move-constructible (Rule of 0)")
{
    static_assert(
        std::is_move_constructible_v<GameInventory::Inventory>,
        "Inventory must be move-constructible");

    GameInventory::Inventory source(2);
    source.addItemOrThrow(
        std::make_unique<GameInventory::Weapon>("Sword", 1.0, 10));

    auto dest = std::move(source);
    REQUIRE(dest.size() == 1);
    REQUIRE(dest.getSlot(0).has_value());
}

TEST_CASE("Inventory recalcStats sums damage, defense, and weight")
{
    GameInventory::Inventory bag(3);
    bag.addItemOrThrow(
        std::make_unique<GameInventory::Weapon>("Sword", 3.0, 20));
    bag.addItemOrThrow(
        std::make_unique<GameInventory::Armor>("Shield", 5.0, 10));

    bag.recalcStats();
    const auto& stats = bag.getStatCache();

    REQUIRE(stats[0] == 20.0f);
    REQUIRE(stats[1] == 10.0f);
    REQUIRE(stats[2] == 8.0f);
    REQUIRE(stats[3] == 2.0f);
}

TEST_CASE("ItemFactory creates polymorphic items")
{
    auto weapon = GameInventory::ItemFactory::createWeapon("Bow", 2.5, 12);
    auto armor  = GameInventory::ItemFactory::createArmor("Helmet", 1.0, 6);

    REQUIRE(weapon->getName() == "Bow");
    REQUIRE(weapon->getWeight() == 2.5);
    REQUIRE(armor->getName() == "Helmet");
    REQUIRE(armor->getWeight() == 1.0);
    REQUIRE(weapon->equip() == "Equipped Bow (dmg=12)");
    REQUIRE(armor->equip() == "Wearing Helmet (def=6)");
}

TEST_CASE("Item clone produces independent copy")
{
    GameInventory::Weapon sword("Sword", 5.0, 15);
    auto cloned = sword.clone();

    REQUIRE(cloned->getName() == "Sword");
    REQUIRE(cloned->getWeight() == 5.0);
    REQUIRE(cloned->equip() == "Equipped Sword (dmg=15)");
}
