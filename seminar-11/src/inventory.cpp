#include "inventory.hpp"

#include <sstream>
#include <utility>

namespace inventory {

namespace {

std::string slotMessage(std::string_view prefix, std::size_t index)
{
    std::ostringstream message;
    message << prefix << " at index " << index;
    return message.str();
}

} // namespace

InventoryException::InventoryException(const std::string& message)
    : std::runtime_error(message)
{
}

SlotOccupiedException::SlotOccupiedException(std::size_t index)
    : InventoryException(slotMessage("Slot is occupied", index))
{
}

EmptySlotException::EmptySlotException(std::size_t index)
    : InventoryException(slotMessage("Slot is empty", index))
{
}

ItemLimitExceededException::ItemLimitExceededException(std::size_t capacity)
    : InventoryException("Inventory item limit exceeded: capacity is " +
                         std::to_string(capacity))
{
}

DurabilityZeroException::DurabilityZeroException(std::string_view itemName)
    : InventoryException("Item durability is zero: " + std::string(itemName))
{
}

InvalidItemTypeException::InvalidItemTypeException(std::string_view itemName)
    : InventoryException("Item is not equipment: " + std::string(itemName))
{
}

std::string toString(InventoryError error)
{
    switch (error) {
    case InventoryError::SlotOutOfRange:
        return "slot out of range";
    case InventoryError::SlotOccupied:
        return "slot occupied";
    case InventoryError::EmptySlot:
        return "empty slot";
    case InventoryError::ItemLimitExceeded:
        return "item limit exceeded";
    }

    return "unknown inventory error";
}

Item::Item(std::string_view id, double weight)
    : id_(id)
    , weight_(weight)
{
}

const std::string& Item::getId() const
{
    return id_;
}

double Item::getWeight() const
{
    return weight_;
}

Equipment::Equipment(std::string_view name, int durability)
    : Equipment(name, 0.0, durability)
{
}

Equipment::Equipment(std::string_view name, double weight, int durability)
    : Item(name, weight)
    , durability_(durability)
{
}

int Equipment::getDurability() const
{
    return durability_;
}

void Equipment::repair(int durability)
{
    durability_ = durability;
}

std::string Equipment::equip() const
{
    if (durability_ <= 0) {
        throw DurabilityZeroException(getId());
    }

    return "Equipped " + getId();
}

std::string Equipment::use()
{
    if (durability_ <= 0) {
        throw DurabilityZeroException(getId());
    }

    --durability_;
    return "Used equipment " + getId();
}

std::unique_ptr<Item> Equipment::clone() const
{
    return std::make_unique<Equipment>(*this);
}

Consumable::Consumable(std::string_view name, int healPower)
    : Consumable(name, 0.0, healPower)
{
}

Consumable::Consumable(std::string_view name, double weight, int healPower)
    : Item(name, weight)
    , healPower_(healPower)
{
}

int Consumable::getHealPower() const
{
    return healPower_;
}

bool Consumable::isConsumed() const
{
    return consumed_;
}

std::string Consumable::use()
{
    if (consumed_) {
        return "Consumable " + getId() + " is already consumed";
    }

    consumed_ = true;
    return "Consumed " + getId() + " and restored " +
           std::to_string(healPower_) + " hp";
}

std::unique_ptr<Item> Consumable::clone() const
{
    return std::make_unique<Consumable>(*this);
}

Inventory::Inventory(std::size_t capacity)
    : slots_(capacity)
{
}

std::size_t Inventory::capacity() const
{
    return slots_.size();
}

std::size_t Inventory::size() const
{
    std::size_t filled = 0;
    for (const auto& slot : slots_) {
        if (slot) {
            ++filled;
        }
    }

    return filled;
}

std::expected<bool, InventoryError> Inventory::addItem(
    std::size_t index,
    std::unique_ptr<Item> item)
{
    if (index >= slots_.size()) {
        return std::unexpected(InventoryError::SlotOutOfRange);
    }
    if (slots_[index]) {
        return std::unexpected(InventoryError::SlotOccupied);
    }
    if (!item || size() >= capacity()) {
        return std::unexpected(InventoryError::ItemLimitExceeded);
    }

    slots_[index] = std::move(item);
    return true;
}

std::expected<bool, InventoryError> Inventory::addItem(std::unique_ptr<Item> item)
{
    if (!item || size() >= capacity()) {
        return std::unexpected(InventoryError::ItemLimitExceeded);
    }

    for (auto& slot : slots_) {
        if (!slot) {
            slot = std::move(item);
            return true;
        }
    }

    return std::unexpected(InventoryError::ItemLimitExceeded);
}

std::expected<bool, InventoryError> Inventory::removeItem(std::size_t index)
{
    if (index >= slots_.size()) {
        return std::unexpected(InventoryError::SlotOutOfRange);
    }
    if (!slots_[index]) {
        return std::unexpected(InventoryError::EmptySlot);
    }

    slots_[index].reset();
    return true;
}

void Inventory::addItemOrThrow(std::size_t index, std::unique_ptr<Item> item)
{
    const auto result = addItem(index, std::move(item));
    if (result) {
        return;
    }

    switch (result.error()) {
    case InventoryError::SlotOutOfRange:
        checkIndexOrThrow(index);
        break;
    case InventoryError::SlotOccupied:
        throw SlotOccupiedException(index);
    case InventoryError::EmptySlot:
        throw EmptySlotException(index);
    case InventoryError::ItemLimitExceeded:
        throw ItemLimitExceededException(capacity());
    }
}

void Inventory::addItemOrThrow(std::unique_ptr<Item> item)
{
    const auto result = addItem(std::move(item));
    if (result) {
        return;
    }

    throw ItemLimitExceededException(capacity());
}

void Inventory::removeItemOrThrow(std::size_t index)
{
    const auto result = removeItem(index);
    if (result) {
        return;
    }

    switch (result.error()) {
    case InventoryError::SlotOutOfRange:
        checkIndexOrThrow(index);
        break;
    case InventoryError::SlotOccupied:
        throw SlotOccupiedException(index);
    case InventoryError::EmptySlot:
        throw EmptySlotException(index);
    case InventoryError::ItemLimitExceeded:
        throw ItemLimitExceededException(capacity());
    }
}

std::optional<std::reference_wrapper<Item>> Inventory::getSlot(
    std::size_t index)
{
    if (index >= slots_.size() || !slots_[index]) {
        return std::nullopt;
    }

    return *slots_[index];
}

std::optional<std::reference_wrapper<const Item>> Inventory::getSlot(
    std::size_t index) const
{
    if (index >= slots_.size() || !slots_[index]) {
        return std::nullopt;
    }

    return *slots_[index];
}

std::string Inventory::useSlot(std::size_t index)
{
    checkIndexOrThrow(index);
    if (!slots_[index]) {
        throw EmptySlotException(index);
    }

    return slots_[index]->use();
}

std::string Inventory::equipSlot(std::size_t index)
{
    checkIndexOrThrow(index);
    if (!slots_[index]) {
        throw EmptySlotException(index);
    }

    auto* equipment = dynamic_cast<Equipment*>(slots_[index].get());
    if (equipment == nullptr) {
        throw InvalidItemTypeException(slots_[index]->getId());
    }

    return equipment->equip();
}

void Inventory::checkIndexOrThrow(std::size_t index) const
{
    if (index >= slots_.size()) {
        throw std::out_of_range(slotMessage("Slot is out of range", index));
    }
}

} // namespace inventory
