cmake_minimum_required(VERSION 3.5)

project(library_fund)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")

add_library(library_fund_lib
    OBJECT
        src/book.cpp
        src/catalog.cpp
        inc/book.hpp
        inc/catalog.hpp
        inc/safe_vector.hpp
)

target_include_directories(library_fund_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE library_fund_lib)

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

    add_executable(unit_tests tests/test_library.cpp)
    target_link_libraries(unit_tests PRIVATE library_fund_lib Catch2::Catch2WithMain)

    add_test(NAME LibraryTests COMMAND unit_tests)

    add_custom_target(run-tests
        COMMAND $<TARGET_FILE:unit_tests>
        DEPENDS unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
