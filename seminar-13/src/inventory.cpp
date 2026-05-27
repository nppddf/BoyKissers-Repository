#include "inventory.hpp"

#include <algorithm>
#include <iostream>

namespace GameInventory {

InventoryException::InventoryException(const std::string& message)
    : std::runtime_error(message)
{
}

ItemLimitExceededException::ItemLimitExceededException(std::size_t capacity)
    : InventoryException("Item limit exceeded: capacity is " +
                         std::to_string(capacity))
{
}

EmptySlotException::EmptySlotException(std::size_t index)
    : InventoryException("Slot is empty at index " + std::to_string(index))
{
}

StatBlock::StatBlock(std::size_t size): _stats(new float[size]()), _size(size)
{
    std::cout << "[LOG] StatBlock alloc: " << _size << " stats @"
              << static_cast<void*>(_stats) << '\n';
}

StatBlock::~StatBlock()
{
    if(_stats)
        std::cout << "[DESTROY] StatBlock freed: " << _size << " stats @"
                  << static_cast<void*>(_stats) << '\n';
    delete[] _stats;
}

StatBlock::StatBlock(const StatBlock& other)
    : _stats(new float[other._size]), _size(other._size)
{
    std::copy(other._stats, other._stats + _size, _stats);
    std::cout << "  [COPY] StatBlock deep copied. Original unchanged." << " @"
              << static_cast<void*>(_stats) << '\n';
}

StatBlock& StatBlock::operator=(const StatBlock& other)
{
    if(this == &other)
        return *this;

    auto* newStats = new float[other._size];
    std::copy(other._stats, other._stats + other._size, newStats);

    delete[] _stats;
    _stats = newStats;
    _size = other._size;

    std::cout << "  [COPY] StatBlock copy-assigned." << " @"
              << static_cast<void*>(_stats) << '\n';
    return *this;
}

StatBlock::StatBlock(StatBlock&& other) noexcept
    : _stats(other._stats), _size(other._size)
{
    other._stats = nullptr;
    other._size = 0;
    std::cout << "  [MOVE] StatBlock moved. Source cleared." << " @"
              << static_cast<void*>(_stats) << '\n';
}

StatBlock& StatBlock::operator=(StatBlock&& other) noexcept
{
    if(this == &other)
        return *this;

    delete[] _stats;
    _stats = other._stats;
    _size = other._size;
    other._stats = nullptr;
    other._size = 0;

    std::cout << "  [MOVE] StatBlock move-assigned. Source cleared." << " @"
              << static_cast<void*>(_stats) << '\n';
    return *this;
}

float& StatBlock::operator[](std::size_t index) { return _stats[index]; }

float StatBlock::operator[](std::size_t index) const { return _stats[index]; }

std::size_t StatBlock::size() const { return _size; }

Item::Item(std::string_view name, double weight): _name(name), _weight(weight)
{
}

const std::string& Item::getName() const { return _name; }

double Item::getWeight() const { return _weight; }

Weapon::Weapon(std::string_view name, int damage): Weapon(name, 0.0, damage) {}

Weapon::Weapon(std::string_view name, double weight, int damage)
    : Item(name, weight), _damage(damage)
{
    std::cout << "[LOG] Weapon created: " << getName() << " (dmg=" << _damage
              << ")\n";
}

int Weapon::getDamage() const { return _damage; }

std::string Weapon::equip() const
{
    return "Equipped " + getName() + " (dmg=" + std::to_string(_damage) + ")";
}

std::unique_ptr<Item> Weapon::clone() const
{
    return std::make_unique<Weapon>(*this);
}

Armor::Armor(std::string_view name, int defense): Armor(name, 0.0, defense) {}

Armor::Armor(std::string_view name, double weight, int defense)
    : Item(name, weight), _defense(defense)
{
    std::cout << "[LOG] Armor created: " << getName() << " (def=" << _defense
              << ")\n";
}

int Armor::getDefense() const { return _defense; }

std::string Armor::equip() const
{
    return "Wearing " + getName() + " (def=" + std::to_string(_defense) + ")";
}

std::unique_ptr<Item> Armor::clone() const
{
    return std::make_unique<Armor>(*this);
}

Inventory::Inventory(std::size_t capacity)
    : _statCache(STAT_COUNT), _items(capacity)
{
}

std::size_t Inventory::capacity() const { return _items.size(); }

std::size_t Inventory::size() const
{
    std::size_t count = 0;
    for(const auto& slot: _items)
        if(slot)
            ++count;
    return count;
}

std::optional<bool> Inventory::addItem(std::unique_ptr<Item> item)
{
    if(!item || size() >= capacity())
        return std::nullopt;

    for(auto& slot: _items)
    {
        if(!slot)
        {
            slot = std::move(item);
            return true;
        }
    }

    return std::nullopt;
}

void Inventory::addItemOrThrow(std::unique_ptr<Item> item)
{
    if(!addItem(std::move(item)))
        throw ItemLimitExceededException(capacity());
}

void Inventory::removeItemOrThrow(std::size_t index)
{
    if(index >= _items.size())
        throw std::out_of_range("Slot out of range: " + std::to_string(index));
    if(!_items[index])
        throw EmptySlotException(index);

    _items[index].reset();
}

std::optional<std::reference_wrapper<Item>>
Inventory::getSlot(std::size_t index)
{
    if(index >= _items.size() || !_items[index])
        return std::nullopt;
    return *_items[index];
}

std::optional<std::reference_wrapper<const Item>>
Inventory::getSlot(std::size_t index) const
{
    if(index >= _items.size() || !_items[index])
        return std::nullopt;
    return *_items[index];
}

std::string Inventory::equipSlot(std::size_t index)
{
    if(index >= _items.size())
        throw std::out_of_range("Slot out of range: " + std::to_string(index));
    if(!_items[index])
        throw EmptySlotException(index);

    return _items[index]->equip();
}

void Inventory::recalcStats()
{
    for(std::size_t i = 0; i < _statCache.size(); ++i)
        _statCache[i] = 0.0f;

    for(const auto& slot: _items)
    {
        if(!slot)
            continue;

        if(auto* weapon = dynamic_cast<Weapon*>(slot.get()))
            _statCache[0] += static_cast<float>(weapon->getDamage());
        else if(auto* armor = dynamic_cast<Armor*>(slot.get()))
            _statCache[1] += static_cast<float>(armor->getDefense());

        _statCache[2] += static_cast<float>(slot->getWeight());
    }

    _statCache[3] = static_cast<float>(size());
}

const StatBlock& Inventory::getStatCache() const { return _statCache; }

}
