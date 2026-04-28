# Seminar 11 - «Игровой инвентарь»

Учебный проект про ООП, исключения и современные контейнеры стандартной
библиотеки. Основа - игровой инвентарь с фиксированным числом слотов,
полиморфными предметами и фабрикой, которая возвращает `std::variant`.

## Возможности

- **`Item`**: базовый полиморфный класс с `id`, `weight`, виртуальным `use()`
  и `clone()`.
- **`Equipment`**: снаряжение с `durability`; сломанный предмет выбрасывает
  `DurabilityZeroException`.
- **`Consumable`**: расходник с `heal_power`, который можно использовать один
  раз.
- **`Inventory`**: фиксированный массив слотов на базе `std::vector` с
  `std::unique_ptr<Item>`, операциями добавления/удаления через
  `std::expected<bool, InventoryError>` и throwing-обертками.
- **`ItemFactory`**: создает `std::variant<Equipment, Consumable>` и
  полиморфные копии предметов через `std::visit`.
- **Unit-тесты (Catch2)**: проверяют ошибки слотов, `optional`-доступ,
  полиморфное использование предметов и работу фабрики.

> В C++ нельзя объявить `std::optional<Item&>`, поэтому метод слота возвращает
> стандартный эквивалент: `std::optional<std::reference_wrapper<Item>>`.

## Структура

```
seminar-11/
├── CMakeLists.txt
├── Readme.md
├── inc/
│   ├── inventory.hpp
│   └── item_factory.hpp
├── src/
│   ├── inventory.cpp
│   ├── item_factory.cpp
│   └── main.cpp
└── tests/
    └── test_inventory.cpp
```

## Требования

- CMake >= 3.5
- Компилятор с поддержкой C++23 (`std::expected`)
- Доступ к Git для загрузки Catch2 при `BUILD_TESTS=ON`

## Сборка и запуск

```bash
cmake -S seminar-11 -B seminar-11/build
cmake --build seminar-11/build
./seminar-11/build/game_inventory
```

## Тесты

```bash
cmake -S seminar-11 -B seminar-11/build -DBUILD_TESTS=ON
cmake --build seminar-11/build --target run-tests
```
