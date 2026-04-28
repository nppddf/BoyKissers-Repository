#pragma once

#include <cstddef>
#include <expected>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace inventory {

class InventoryException : public std::runtime_error {
public:
    explicit InventoryException(const std::string& message);
};

class SlotOccupiedException : public InventoryException {
public:
    explicit SlotOccupiedException(std::size_t index);
};

class EmptySlotException : public InventoryException {
public:
    explicit EmptySlotException(std::size_t index);
};

class ItemLimitExceededException : public InventoryException {
public:
    explicit ItemLimitExceededException(std::size_t capacity);
};

class DurabilityZeroException : public InventoryException {
public:
    explicit DurabilityZeroException(std::string_view itemName);
};

class InvalidItemTypeException : public InventoryException {
public:
    explicit InvalidItemTypeException(std::string_view itemName);
};

enum class InventoryError {
    SlotOutOfRange,
    SlotOccupied,
    EmptySlot,
    ItemLimitExceeded,
};

std::string toString(InventoryError error);

class Item {
public:
    explicit Item(std::string_view id, double weight);
    virtual ~Item() = default;

    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;

    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] double getWeight() const;

    virtual std::string use() = 0;
    virtual std::unique_ptr<Item> clone() const = 0;

private:
    std::string id_;
    double weight_;
};

class Equipment final : public Item {
public:
    explicit Equipment(std::string_view name, int durability);
    Equipment(std::string_view name, double weight, int durability);

    [[nodiscard]] int getDurability() const;
    void repair(int durability);
    std::string equip() const;
    std::string use() override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

private:
    int durability_;
};

class Consumable final : public Item {
public:
    explicit Consumable(std::string_view name, int healPower);
    Consumable(std::string_view name, double weight, int healPower);

    [[nodiscard]] int getHealPower() const;
    [[nodiscard]] bool isConsumed() const;
    std::string use() override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

private:
    int healPower_;
    bool consumed_ = false;
};

class Inventory {
public:
    explicit Inventory(std::size_t capacity);

    [[nodiscard]] std::size_t capacity() const;
    [[nodiscard]] std::size_t size() const;

    std::expected<bool, InventoryError> addItem(
        std::size_t index,
        std::unique_ptr<Item> item);
    std::expected<bool, InventoryError> addItem(std::unique_ptr<Item> item);
    std::expected<bool, InventoryError> removeItem(std::size_t index);

    void addItemOrThrow(std::size_t index, std::unique_ptr<Item> item);
    void addItemOrThrow(std::unique_ptr<Item> item);
    void removeItemOrThrow(std::size_t index);

    std::optional<std::reference_wrapper<Item>> getSlot(std::size_t index);
    std::optional<std::reference_wrapper<const Item>> getSlot(
        std::size_t index) const;

    std::string useSlot(std::size_t index);
    std::string equipSlot(std::size_t index);

private:
    void checkIndexOrThrow(std::size_t index) const;

    std::vector<std::unique_ptr<Item>> slots_;
};

} // namespace inventory
