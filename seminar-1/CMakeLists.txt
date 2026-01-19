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
add_library( function_parser_lib 
    OBJECT
        src/function_parser.cpp
        inc/function_parser.h
)
    
target_include_directories( function_parser_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Link math library for sin, cos, exp functions
target_link_libraries( function_parser_lib PUBLIC m )

# --- 3. Main Application ---
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE function_parser_lib m)

# --- 4. Testing Setup ---
enable_testing()

add_executable(unit_tests EXCLUDE_FROM_ALL tests/test_calculator.cpp)

# Link the test to our logic AND the Catch2 library
target_link_libraries(unit_tests PRIVATE function_parser_lib Catch2::Catch2WithMain)
# Register the test with CTest
add_test(NAME FunctionParserTests COMMAND unit_tests)

add_custom_target(run-tests
  COMMAND $<TARGET_FILE:unit_tests>
  DEPENDS unit_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)