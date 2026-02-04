# Seminar 4 - Text Utils

A small command-line utility that reads a full name (Фамилия Имя Отчество), validates the input, and prints it in
multiple formats. This project demonstrates basic wide-string processing in C++, CMake configuration, and unit testing
with Catch2.

## Features

- **Input validation**: Allows only letters and spaces in the entered full name
- **Formatting**:
  - UPPERCASE: `ФАМИЛИЯ ИМЯ ОТЧЕСТВО`
  - Capitalized words: `Фамилия Имя Отчество`
  - Short form: `Фамилия И. О.`
- **Modular design**: Core logic is built as a library and reused by both the app and tests
- **Unit testing**: Catch2-based test suite for parsing and formatting

## Project Structure

```
seminar-4/
├── CMakeLists.txt            # CMake build configuration
├── Readme.md                 # This file
├── inc/                      # Header files
│   └── name_utils.h          # Name utilities declarations
├── src/                      # Source files
│   ├── main.cpp              # Main application entry point
│   └── name_utils.cpp        # Name utilities implementation
└── tests/                    # Test files
    └── test_name_utils.cpp   # Unit tests using Catch2
```

## Requirements

- **CMake** (version 3.5 or higher)
- **C++ compiler** with C++17 support (GCC, Clang, or MSVC)
- **Git** (for fetching Catch2 dependency)

## Dependencies

The project automatically fetches **Catch2** (v3.4.0) via CMake `FetchContent`. No manual installation required.

## Build

### Initial Configuration

```bash
cmake -S . -B build
```

### Compilation

```bash
cmake --build build
```

This will create:
- `build/text_utils` - The main executable
- `build/unit_tests` - The test executable

## Run

```bash
./build/text_utils
```

The program will prompt you for full name input and print three formatting variants.

## Unit Testing

Run the test suite:

```bash
cmake --build build --target run-tests
```

All tests are based on Catch2 and are executed via the `run-tests` target (also registered in CTest as
`NameUtilsTests`).

## Architecture

The project follows a modular design:
- **Library module** (`text_utils_lib`): contains the core name formatting logic
- **Main application**: links against the library to provide the CLI interface
- **Test suite**: links against the same library to test logic without code duplication

