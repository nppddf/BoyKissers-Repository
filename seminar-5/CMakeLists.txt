cmake_minimum_required(VERSION 3.5)

project(xor_cipher_utils)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_library(xor_cipher_utils_lib
    OBJECT
        src/xor_cipher_utils.cpp
        inc/xor_cipher_utils.hpp
)

target_include_directories(xor_cipher_utils_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE xor_cipher_utils_lib)


# --- Testing Setup ---
option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(unit_tests tests/test_xor_cipher_utils.cpp)

    target_link_libraries(unit_tests PRIVATE xor_cipher_utils_lib Catch2::Catch2WithMain)
    add_test(NAME XorCipherUtilsTests COMMAND unit_tests)

    add_custom_target(run-tests
      COMMAND $<TARGET_FILE:unit_tests>
      DEPENDS unit_tests
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
