cmake_minimum_required(VERSION 3.5)

project(WorkshopX CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

# the following options prevent compiler-optimization issues that are unwanted in an edu process
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# --- 1. Fetch Catch2 Dependency ---
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0 # Or latest version
)
FetchContent_MakeAvailable(Catch2)

# --- 2. Create a Library for shared logic ---
# Instead of compiling calculator.cpp twice, we make it a library
add_library(MathLib src/calculator.cpp)
target_include_directories(MathLib PUBLIC include)

# --- 3. Main Application ---
add_executable(MyApp src/main.cpp)
target_link_libraries(MyApp PRIVATE MathLib)

# --- 4. Testing Setup ---
enable_testing()

add_executable(unit_tests tests/test_calculator.cpp)

# Link the test to our logic AND the Catch2 library
target_link_libraries(unit_tests PRIVATE MathLib Catch2::Catch2WithMain)
# Register the test with CTest
add_test(NAME MyCalculatorTests COMMAND unit_tests)