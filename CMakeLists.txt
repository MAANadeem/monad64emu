cmake_minimum_required(VERSION 3.20)
project(n64_emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Always generate compile_commands.json (good for clangd / Neovim)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# --------------------
# Compiler warnings
# --------------------
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

# Debug vs Release flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O0 -g)
else()
    add_compile_options(-O3 -DNDEBUG)
endif()

# --------------------
# Executable
# --------------------
add_executable(n64_emulator
    src/memmap.cpp
    src/CPU/cpu.cpp
    src/CPU/cp0.cpp
    src/rpc.cpp
    src/N64.cpp
    src/main.cpp
)

target_include_directories(n64_emulator PRIVATE include)
