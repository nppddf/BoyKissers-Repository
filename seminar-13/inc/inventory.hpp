#ifndef SEMINAR_13_INVENTORY_HPP
#define SEMINAR_13_INVENTORY_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace GameInventory {

class InventoryException: public std::runtime_error
{
public:
    explicit InventoryException(const std::string& message);
};

class ItemLimitExceededException: public InventoryException
{
public:
    explicit ItemLimitExceededException(std::size_t capacity);
};

class EmptySlotException: public InventoryException
{
public:
    explicit EmptySlotException(std::size_t index);
};

class StatBlock
{
public:
    explicit StatBlock(std::size_t size);
    ~StatBlock();

    StatBlock(const StatBlock& other);
    StatBlock& operator=(const StatBlock& other);
    StatBlock(StatBlock&& other) noexcept;
    StatBlock& operator=(StatBlock&& other) noexcept;

    float& operator[](std::size_t index);
    float operator[](std::size_t index) const;
    [[nodiscard]] std::size_t size() const;

private:
    float* _stats;
    std::size_t _size;
};

class Item
{
public:
    Item(std::string_view name, double weight);
    virtual ~Item() = default;

    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] double getWeight() const;

    virtual std::string equip() const = 0;
    [[nodiscard]] virtual std::unique_ptr<Item> clone() const = 0;

private:
    std::string _name;
    double _weight;
};

class Weapon final: public Item
{
public:
    Weapon(std::string_view name, int damage);
    Weapon(std::string_view name, double weight, int damage);

    [[nodiscard]] int getDamage() const;
    std::string equip() const override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

private:
    int _damage;
};

class Armor final: public Item
{
public:
    Armor(std::string_view name, int defense);
    Armor(std::string_view name, double weight, int defense);

    [[nodiscard]] int getDefense() const;
    std::string equip() const override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

private:
    int _defense;
};

class Inventory
{
public:
    static constexpr std::size_t STAT_COUNT = 5;

    explicit Inventory(std::size_t capacity);

    [[nodiscard]] std::size_t capacity() const;
    [[nodiscard]] std::size_t size() const;

    std::optional<bool> addItem(std::unique_ptr<Item> item);
    void addItemOrThrow(std::unique_ptr<Item> item);
    void removeItemOrThrow(std::size_t index);

    std::optional<std::reference_wrapper<Item>> getSlot(std::size_t index);
    std::optional<std::reference_wrapper<const Item>>
    getSlot(std::size_t index) const;

    std::string equipSlot(std::size_t index);
    void recalcStats();
    [[nodiscard]] const StatBlock& getStatCache() const;

private:
    StatBlock _statCache;
    std::vector<std::unique_ptr<Item>> _items;
};

}  // namespace GameInventory

#endif
