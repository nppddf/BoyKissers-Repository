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
        inc/plus.h
)
    
target_include_directories( plus_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# --- 3. Main Application ---
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE plus_lib)

# --- 4. Testing Setup ---
