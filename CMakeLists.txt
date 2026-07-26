cmake_minimum_required(VERSION 3.16.0)
project(Heroes3App LANGUAGES CXX)
set(APP_NAME Heroes3App)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include FetchContent module
include(FetchContent)

add_compile_options(-lsfml-graphics -lsfml-window -lsfml-system)

# === Dependencies ===
# Declare and fetch googletest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0 # Use a specific stable tag instead of main
)

FetchContent_MakeAvailable(googletest)

# Declare and fetch sfml
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

# List of project source files
set(MODULES
    Algorithms
    Artifacts
    Battle
    Characters
    Game
    Graphic
    LoadAndSaveTools
    Magic
    Miscellaneous
    Player

    # Resource
    Units
    WorldMap
    CACHE INTERNAL "List of module targets"
)

# === Compilation flags ===
function(enable_compiler_flags target)
    if(TARGET ${target})
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Werror -g
            -Wnull-dereference -Wdouble-promotion
            -Wshadow -Wconversion -Wsign-conversion -Wformat=2

            # -fsanitize=address -fsanitize=undefined
        )
    else()
        message(WARNING "Target '${target}' not found - skipping compiler flags")
    endif()
endfunction()

foreach(module ${MODULES})
    add_subdirectory(src/${module})
    target_link_libraries(${module} PRIVATE sfml-system)
    enable_compiler_flags(${module})
    set_target_properties(${module} PROPERTIES
        CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
    target_compile_features(${module} PUBLIC cxx_std_20)
endforeach()

# === Executable ===
add_subdirectory(app)
enable_compiler_flags(${APP_NAME})
set_target_properties(${APP_NAME} PROPERTIES
    CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

# === Tests ===
enable_testing()
add_subdirectory(tests)