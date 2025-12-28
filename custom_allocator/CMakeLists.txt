cmake_minimum_required(VERSION 3.10)
project(AllocatorBenchmark)

# 1. Set C++ standard (C++17 or higher is recommended for modern allocators)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Tell CMake where to find your .h files
# This allows you to use #include "allocator.h" instead of "../include/allocator.h"
include_directories(include)

# 3. Collect all source files
# It's better to list them explicitly so you notice if a file is missing
set(SOURCES 
    main.cpp
    benchmark.cpp
    stack_allocator.cpp
)

# 4. Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. (Optional) Add compiler warnings to help catch bugs in your allocator logic
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()