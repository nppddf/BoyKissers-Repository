cmake_minimum_required(VERSION 3.5)

project(game_inventory_raii)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")

add_library(game_inventory_raii_lib
    OBJECT
        src/inventory.cpp
        src/item_factory.cpp
        inc/inventory.hpp
        inc/item_factory.hpp
)

target_include_directories(game_inventory_raii_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE game_inventory_raii_lib)

option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(unit_tests tests/test_stat_block.cpp)
    target_link_libraries(unit_tests PRIVATE game_inventory_raii_lib
                          Catch2::Catch2WithMain)

    add_test(NAME InventoryRaiiTests COMMAND unit_tests)

    add_custom_target(run-tests
        COMMAND $<TARGET_FILE:unit_tests>
        DEPENDS unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
