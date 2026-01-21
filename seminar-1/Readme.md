# Seminar 1 - Simple Calculator

A lightweight command-line calculator application that performs addition operations on two integer numbers. This project demonstrates basic C++ programming concepts, CMake build system configuration, and unit testing with Catch2.

## Features

- **Interactive Input**: Continuously reads pairs of integers from standard input
- **Error Handling**: Validates input and handles invalid entries gracefully
- **Large Number Support**: Uses `long long` type to support large integer values
- **Unit Testing**: Comprehensive test suite covering positive, negative, and edge cases
- **Modular Design**: Separated library code for easy testing and reuse

## Project Structure

```
seminar-1/
├── CMakeLists.txt          # CMake build configuration
├── Readme.md               # This file
├── inc/                    # Header files
│   └── plus.h             # Addition function declaration
├── src/                    # Source files
│   ├── main.cpp           # Main application entry point
│   └── plus.cpp           # Addition function implementation
└── tests/                  # Test files
    └── test_calculator.cpp # Unit tests using Catch2
```

## Requirements

- **CMake** (version 3.5 or higher)
- **C++ Compiler** with C++17 support (GCC, Clang, or MSVC)
- **Git** (for fetching Catch2 dependency)

## Dependencies

The project automatically fetches **Catch2** (v3.4.0) as a testing framework via CMake's `FetchContent` module. No manual installation required.

## Build

### Initial Configuration
Configure the build system (only needed once):
```bash
cmake -S . -B build
```

### Compilation
Build the project:
```bash
cmake --build build
```

This will create:
- `build/100_percentil` - The main executable
- `build/unit_tests` - The test executable

## Run

Execute the calculator application:
```bash
./build/100_percentil
```

The program will prompt you to enter two integer numbers. It will:
- Display the sum of the two numbers
- Continue accepting new pairs of numbers until terminated (Ctrl+C)
- Handle invalid input by clearing the error state and prompting again

### Example Usage

```
Summator - enter two integer numbers:
5 10
15
-3 7
4
100 200
300
```

## Unit Testing

Run the test suite:
```bash
cmake --build build --target run-tests
```

The test suite includes:
- **Positive numbers**: Tests addition of positive integers
- **Zero handling**: Tests edge cases with zero
- **Negative numbers**: Tests addition with negative integers
- **Commutativity**: Verifies that addition is commutative (a + b = b + a)

All tests use the Catch2 testing framework and are automatically executed when you run the test target.

## Architecture

The project follows a modular design:
- **Library Module** (`plus_lib`): Contains the core addition logic as an object library
- **Main Application**: Links against the library to provide the interactive calculator interface
- **Test Suite**: Links against the same library to ensure correctness without code duplication

This architecture allows the same implementation to be used by both the application and tests, ensuring consistency and maintainability.