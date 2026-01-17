cmake_minimum_required(VERSION 3.5)

project(100_percentil)

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
add_library( plus_lib 
    OBJECT
        src/plus.cpp
        src/function_parser.cpp
        inc/plus.h
        inc/function_parser.h
)
    
target_include_directories( plus_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Link math library for sin, cos, exp functions
target_link_libraries( plus_lib PUBLIC m )

# --- 3. Main Application ---
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE plus_lib m)

# --- 4. Testing Setup ---
enable_testing()

add_executable(unit_tests EXCLUDE_FROM_ALL tests/test_calculator.cpp)

# Link the test to our logic AND the Catch2 library
target_link_libraries(unit_tests PRIVATE plus_lib Catch2::Catch2WithMain)
# Register the test with CTest
add_test(NAME MyCalculatorTests COMMAND unit_tests)

add_custom_target(run-tests
  COMMAND $<TARGET_FILE:unit_tests>
  DEPENDS unit_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)