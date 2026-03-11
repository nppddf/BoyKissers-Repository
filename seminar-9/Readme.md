# Seminar 9 – «Библиотечный фонд»

Учебный проект о семантике копирования и безопасном управлении динамической
памятью. Основа — библиотечный каталог, построенный на классе `Book`
(вместо структур) и собственном векторе `SafeVector<Book>` с корректным
копированием и изменяемым размером.

## Возможности

- **`Book` (Rule of Three)**: глубокое копирование `title` (`char*`), явные
  конструктор копирования, оператор присваивания и деструктор.
- **`SafeVector<T>`**: простой динамический массив уровня семинара — отдельные
  буферы при копировании, `resize`, `push_back`, безопасный `at()`.
- **Каталог**: хранение книг в `SafeVector<Book>`, сортировка кастомным
  компаратором по году, длине названия и алфавиту (через `std::tie`).
- **Unit-тесты** (Catch2): проверяют глубокое копирование и порядок сортировки.

## Структура

```
seminar-9/
├── CMakeLists.txt          # CMake-конфигурация (app + tests)
├── Readme.md               # это описание
├── inc/
│   ├── book.hpp            # класс Book
│   ├── catalog.hpp         # каталог книг и компаратор
│   └── safe_vector.hpp     # шаблон SafeVector
├── src/
│   ├── book.cpp
│   ├── catalog.cpp
│   └── main.cpp            # демонстрационная консольная программа
└── tests/
    └── test_library.cpp    # Catch2 тесты
```

## Требования

- CMake ≥ 3.5
- Компилятор с поддержкой C++17
- Доступ к Git (для FetchContent Catch2 при `BUILD_TESTS=ON`)

## Сборка и запуск

```bash
cmake -S seminar-9 -B seminar-9/build
cmake --build seminar-9/build
./seminar-9/build/library_fund
```

## Тесты

```bash
cmake -S seminar-9 -B seminar-9/build -DBUILD_TESTS=ON
cmake --build seminar-9/build --target run-tests
```

Будет собран исполняемый файл `unit_tests`, а цель `run-tests` запустит все
проверки Catch2.
