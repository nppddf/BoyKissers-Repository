# Seminar 4 - Kadane Utils

A small command-line utility that reads an integer matrix and finds the maximum-sum submatrix using the 2D Kadane
algorithm. The project demonstrates matrix processing, reusable C++ utilities, and optional unit testing with Catch2.

## Features

- **Matrix input**: Reads dimensions followed by matrix elements from stdin
- **2D Kadane algorithm**: Finds the submatrix with the maximal sum
- **Coordinate output**: Prints the top-left and bottom-right coordinates of the best submatrix
- **Modular design**: Core logic lives in a library reused by the app and tests
- **Unit testing**: Catch2-based tests for edge cases and I/O helpers (optional build)

## Project Structure

```
seminar-4/
├── CMakeLists.txt              # CMake build configuration
├── Readme.md                   # This file
├── inc/                        # Header files
│   └── kadane_utils.hpp         # Kadane utilities declarations
├── src/                        # Source files
│   ├── main.cpp                # Main application entry point
│   └── kadane_utils.cpp         # Kadane utilities implementation
└── tests/                      # Test files
    └── test_kadane_utils.cpp    # Unit tests using Catch2
```

## Requirements

- **CMake** (version 3.5 or higher)
- **C++ compiler** with C++17 support (GCC, Clang, or MSVC)
- **Git** (for fetching Catch2 when tests are enabled)

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
- `build/kadane_utils` - The main executable

## Run

```bash
./build/kadane_utils
```

Input format:

```
<rows> <cols>
<row_0_values>
<row_1_values>
...
```

The program prints the maximum sum, submatrix coordinates, and the submatrix itself.

## Unit Testing

Tests are built only when enabled explicitly:

```bash
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build --target run-tests
```

The test executable is registered in CTest as `KadaneUtilsTests`.

## Architecture

The project follows a modular design:
- **Library module** (`kadane_utils_lib`): contains matrix input, 2D Kadane, and submatrix printing
- **Main application**: links against the library to provide the CLI interface
- **Test suite**: links against the same library to validate behavior
