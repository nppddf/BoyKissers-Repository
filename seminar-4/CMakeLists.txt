cmake_minimum_required(VERSION 3.5)

project(text_utils)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

include(FetchContent)
FetchContent_Declare(
    Catch2  
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_library(text_utils_lib
    OBJECT
        src/name_utils.cpp
        inc/name_utils.h
)

target_include_directories(text_utils_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE text_utils_lib)


# --- 4. Testing Setup ---
enable_testing()

add_executable(unit_tests EXCLUDE_FROM_ALL tests/test_name_utils.cpp)

target_link_libraries(unit_tests PRIVATE text_utils_lib Catch2::Catch2WithMain)
add_test(NAME NameUtilsTests COMMAND unit_tests)

add_custom_target(run-tests
  COMMAND $<TARGET_FILE:unit_tests>
  DEPENDS unit_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
