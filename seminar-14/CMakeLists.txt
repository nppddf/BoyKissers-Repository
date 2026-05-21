cmake_minimum_required(VERSION 3.14)

project(type_safe_units)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")

# Header-only template library — no .cpp sources, so INTERFACE is correct
add_library(units_lib INTERFACE)
target_include_directories(units_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE units_lib)

option(BUILD_TESTS "Build unit tests" OFF)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    set(FETCHCONTENT_SOURCE_DIR_CATCH2
        "${CMAKE_CURRENT_SOURCE_DIR}/../seminar-10/build-tests/_deps/catch2-src"
        CACHE PATH "" FORCE)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(unit_tests tests/test_units.cpp)
    target_link_libraries(unit_tests PRIVATE units_lib Catch2::Catch2WithMain)

    add_test(NAME UnitTests COMMAND unit_tests)

    add_custom_target(run-tests
        COMMAND $<TARGET_FILE:unit_tests>
        DEPENDS unit_tests
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()
