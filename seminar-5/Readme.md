# Seminar 5 - XOR Cipher Utils

A small command-line utility that reads binary files and encrypts or decrypts them with a simple XOR cipher.
The core logic is implemented as a reusable C++ library, with an optional test suite.

## Features

- **Binary I/O**: Read and write files in binary mode
- **XOR cipher**: Encrypt and decrypt with the same internal function
- **Simple CLI**: Encrypt or decrypt a file using a key
- **Modular design**: Reusable library shared by the app and tests
- **Unit testing**: Optional Catch2-based tests

## Project Structure

```
seminar-5/
├── CMakeLists.txt                   # CMake build configuration
├── Readme.md                        # This file
├── inc/                             # Header files
│   └── xor_cipher_utils.hpp          # Binary I/O + XOR cipher declarations
├── src/                             # Source files
│   ├── main.cpp                     # CLI entry point
│   └── xor_cipher_utils.cpp          # Binary I/O + XOR cipher implementation
└── tests/                           # Test files
    └── test_xor_cipher_utils.cpp     # Unit tests using Catch2
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
- `build/xor_cipher_utils` - The main executable

## Run

```bash
./build/xor_cipher_utils encrypt <input_path> <output_path> <key>
./build/xor_cipher_utils decrypt <input_path> <output_path> <key>
```

The XOR cipher is symmetric, so decryption is performed by the same internal routine as encryption.

## Unit Testing

Tests are built only when enabled explicitly:

```bash
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build --target run-tests
```

The test executable is registered in CTest as `XorCipherUtilsTests`.

## Architecture

The project follows a modular design:
- **Library module** (`xor_cipher_utils_lib`): binary file I/O and XOR cipher helpers
- **Main application**: CLI wrapper for file encryption and decryption
- **Test suite**: validates the library behavior using Catch2
