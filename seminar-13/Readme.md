# Seminar 13 — «Инвентарь и управление ресурсами»

Учебный проект про RAII, правило пяти и правило нуля. Инвентарь — лишь
удобная декорация: настоящая тема — как C++ связывает владение ресурсом с
временем жизни объекта и что происходит при копировании или перемещении.

---

## Центральная идея

Когда класс владеет «голым» ресурсом — указателем, файловым дескриптором,
сетевым сокетом — компилятор не знает, что с ним делать при копировании или
уничтожении. Он просто скопирует адрес, и два объекта окажутся владельцами
одной памяти. Это и есть корень ошибок двойного освобождения и утечек.

Решение — **правило пяти**: если хотя бы один специальный метод написан
вручную, остальные четыре тоже нужно определить явно.

Но есть более элегантный путь. Если обернуть ресурс в класс, который уже
знает, как копироваться и перемещаться, то все составные классы получают
корректное поведение автоматически — **правило нуля**.

Проект показывает оба подхода в паре.

---

## Два персонажа

### `StatBlock` — правило пяти

Хранит массив характеристик `float* _stats`. Сырой указатель — это ресурс,
которым нужно управлять вручную.

```
StatBlock(5)          → выделяет память,   пишет [LOG]  alloc
StatBlock(const&)     → глубокое копирование, пишет [COPY]
operator=(const&)     → аллоцирует новый буфер до изменения *this
StatBlock(&&)         → забирает указатель, обнуляет источник, пишет [MOVE]
~StatBlock()          → освобождает память, пишет [DESTROY]
```

Каждая операция с памятью происходит ровно один раз, и каждая видна в
консоли — намеренно, чтобы семантика копирования и перемещения была
буквально наблюдаемой.

Конструктор копирования и оператор копирующего присваивания дают **строгую
гарантию исключений**: `new[]` вызывается до того, как объект изменён, поэтому
при нехватке памяти состояние остаётся прежним.

### `Inventory` — правило нуля

Содержит `StatBlock _statCache` и `std::vector<std::unique_ptr<Item>> _items`.
Ни одного специального метода не написано.

Компилятор сам строит перемещающий конструктор: он вызывает `StatBlock(&&)`,
который печатает `[MOVE]`, и перемещает вектор. Это и делает передачу
инвентаря между игроками дешёвой — вместо глубокого копирования происходит
просто смена владельца указателей.

Попытка скопировать `Inventory` не скомпилируется: `unique_ptr` — не
копируемый, а значит и вектор, и сам инвентарь — тоже.

---

## Иерархия предметов

```
Item  (абстрактный)
 ├── Weapon  — getDamage(), equip() → "Equipped Sword (dmg=15)"
 └── Armor   — getDefense(), equip() → "Wearing Chainmail (def=10)"
```

Наследование здесь — ради полиморфного поведения: `Inventory::equipSlot()`
вызывает виртуальный `equip()`, не зная, что лежит в слоте. `ItemFactory`
создаёт объекты как `unique_ptr<Item>`, сохраняя полиморфизм.

---

## Что происходит при запуске

```
[LOG] StatBlock alloc: 5 stats @0x...       ← combatStats в main
[LOG] Weapon created: Sword (dmg=15)        ← демонстрация конструктора
[LOG] Armor created: Chainmail (def=10)
Equipped Sword (dmg=15)
Wearing Chainmail (def=10)
Inventory copy test:
  [COPY] StatBlock deep copied. Original unchanged. @0x...
  Original stat[0]: 15 (unchanged)          ← копия изменена, оригинал цел
[DESTROY] StatBlock freed: 5 stats @0x...   ← временная копия вышла из области
Looting chest...
[LOG] StatBlock alloc: 5 stats @0x...       ← StatBlock внутри chest
[LOG] Weapon created: Sword (dmg=15)
[LOG] Armor created: Chainmail (def=10)
  [MOVE] Inventory transferred to player.
  [MOVE] StatBlock moved. Source cleared. @0x...  ← return std::move(chest)
Player inventory: [Sword, Chainmail]
Combat stats calculated via cached StatBlock.
  dmg=15  def=10  weight=13
Cleanup: All resources freed.
[DESTROY] StatBlock freed: 5 stats @0x...   ← StatBlock игрока
[DESTROY] StatBlock freed: 5 stats @0x...   ← combatStats из main
```

Почему `lootChest()` использует `return std::move(chest)`, а не просто `return
chest`? При прямом возврате компилятор применяет NRVO и конструирует объект
прямо в памяти вызывающего — перемещение не вызывается, лог остаётся пустым.
`std::move` отключает эту оптимизацию: перемещающий конструктор срабатывает
явно, и семантика владения становится видимой.

---

## Структура

```
seminar-13/
├── CMakeLists.txt
├── Readme.md
├── inc/
│   ├── inventory.hpp      StatBlock, Item, Weapon, Armor, Inventory
│   └── item_factory.hpp   ItemFactory
├── src/
│   ├── inventory.cpp
│   ├── item_factory.cpp
│   └── main.cpp
└── tests/
    └── test_stat_block.cpp
```

Ядро собирается как OBJECT-библиотека `game_inventory_raii_lib`. Исполняемый
файл и тесты линкуются с ней отдельно — никакого дублирования кода.

## Требования

- CMake >= 3.5
- Компилятор с поддержкой C++17
- Git (для загрузки Catch2 при `BUILD_TESTS=ON`)

## Сборка и запуск

```bash
cmake -S seminar-13 -B seminar-13/build
cmake --build seminar-13/build
./seminar-13/build/game_inventory_raii
```

## Тесты

```bash
cmake -S seminar-13 -B seminar-13/build -DBUILD_TESTS=ON
cmake --build seminar-13/build --target run-tests
```

Тесты покрывают: глубокое копирование `StatBlock`, перемещение с очисткой
источника, оба оператора присваивания, полиморфный `equip()`, переполнение
инвентаря, исключения при работе с пустыми слотами, `recalcStats()` и
`ItemFactory`.
