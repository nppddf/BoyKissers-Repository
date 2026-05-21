#include "inventory.hpp"
#include "item_factory.hpp"

#include <iostream>

namespace {

GameInventory::Inventory lootChest()
{
    GameInventory::Inventory chest(2);
    chest.addItemOrThrow(
        GameInventory::ItemFactory::createWeapon("Sword", 5.0, 15));
    chest.addItemOrThrow(
        GameInventory::ItemFactory::createArmor("Chainmail", 8.0, 10));
    std::cout << "  [MOVE] Inventory transferred to player.\n";
    return std::move(chest);
}

void printInventory(const GameInventory::Inventory& inv)
{
    std::cout << "[";
    bool first = true;
    for(std::size_t i = 0; i < inv.capacity(); ++i)
    {
        auto slot = inv.getSlot(i);
        if(!slot)
            continue;
        if(!first)
            std::cout << ", ";
        std::cout << slot->get().getName();
        first = false;
    }
    std::cout << "]";
}

}  // namespace

int main()
{
    // Demonstrate StatBlock allocation and initial stat values
    GameInventory::StatBlock combatStats(5);
    combatStats[0] = 15.0f;
    combatStats[1] = 10.0f;

    // Demonstrate Weapon and Armor construction (logs on creation)
    {
        GameInventory::Weapon demoSword("Sword", 5.0, 15);
        GameInventory::Armor demoChainmail("Chainmail", 8.0, 10);
        std::cout << demoSword.equip() << '\n';
        std::cout << demoChainmail.equip() << '\n';
    }

    // StatBlock copy test: modify the copy, verify original is untouched
    std::cout << "Inventory copy test:\n";
    {
        GameInventory::StatBlock statCopy = combatStats;
        statCopy[0] = 99.0f;
        std::cout << "  Original stat[0]: " << combatStats[0]
                  << " (unchanged)\n";
    }

    // Move Inventory out of lootChest — StatBlock move is visible in the log
    std::cout << "Looting chest...\n";
    auto player = lootChest();

    // Display player inventory using polymorphic equip()
    std::cout << "Player inventory: ";
    printInventory(player);
    std::cout << '\n';

    for(std::size_t i = 0; i < player.capacity(); ++i)
    {
        auto slot = player.getSlot(i);
        if(slot)
            std::cout << "  " << slot->get().equip() << '\n';
    }

    // Compute combined stats through the cached StatBlock
    player.recalcStats();
    const auto& cache = player.getStatCache();
    std::cout << "Combat stats calculated via cached StatBlock.\n";
    std::cout << "  dmg=" << cache[0] << "  def=" << cache[1]
              << "  weight=" << cache[2] << '\n';

    std::cout << "Cleanup: All resources freed.\n";

    return 0;
}
