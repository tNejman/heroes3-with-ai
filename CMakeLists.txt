cmake_minimum_required(VERSION 3.25.0)
project(Heroes3App LANGUAGES CXX)
set(APP_NAME Heroes3App)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type is: ${CMAKE_BUILD_TYPE}")

option(CODE_COVERAGE "code coverage" ON)

# find_program(CLANG_TIDY_EXE NAMES clang-tidy)
# set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" --use-color) #  --fix-errors

include(FetchContent)

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS ON)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    SYSTEM
)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    SYSTEM
)
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG v0.9.7
    SYSTEM
)

set(_saved_clang_tidy "${CMAKE_CXX_CLANG_TIDY}")
set(CMAKE_CXX_CLANG_TIDY "")
FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(magic_enum)
set(CMAKE_CXX_CLANG_TIDY "${_saved_clang_tidy}")

execute_process(
    COMMAND python3 ${CMAKE_SOURCE_DIR}/fetch_sprites.py ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE rc
)
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "sprite fetch failed")
endif()

set(CORE_MODULES
    # Algorithms
    Artifact 
    Battle 
    Character
    Game 
    Magic 
    MapObject
    Misc 
    Player 
    Resource 
    Unit 
    WorldMap
)

set(ENGINE_MODULES
    Graphics
    Input
    LoadAndSaveTools
)

function(apply_compiler_flags target)
    target_compile_options(${target} PRIVATE
        $<$<CONFIG:Debug>:
        -g -O0
        -Wall -Wextra -Wpedantic -Werror 
        -Wcast-align -Wcast-qual 
        -Wconversion -Wsign-conversion -Wshadow 
        -Wdouble-promotion -Wnull-dereference 
        -Wformat=2 
        -Wzero-as-null-pointer-constant 
        -Wvla
        -fno-omit-frame-pointer
        -fsanitize=address
        -fsanitize=undefined
        
        # --coverage
        >

        $<$<CONFIG:Release>:-march=native>
    )
    target_link_options(${target} PUBLIC 
        $<$<CONFIG:Debug>:
        -fsanitize=address,undefined 
        # --coverage
        >
    )
endfunction()

foreach(module ${ENGINE_MODULES})
    add_subdirectory(engine/src/engine/${module})
    target_include_directories(${module} PRIVATE
        ${CMAKE_SOURCE_DIR}/engine/include/
        ${CMAKE_SOURCE_DIR}/aux/include/
        ${CMAKE_SOURCE_DIR}/core/include # @TODO!!! REMOVE
    )
    apply_compiler_flags(${module})
endforeach()

foreach(module ${CORE_MODULES})
    add_subdirectory(core/src/core/${module})
    target_include_directories(${module} PRIVATE 
        ${CMAKE_SOURCE_DIR}/core/include/
        ${CMAKE_SOURCE_DIR}/engine/include/
        ${CMAKE_SOURCE_DIR}/aux/include/
    )
    apply_compiler_flags(${module})
endforeach() 

add_subdirectory(app) 

enable_testing() 
add_subdirectory(test) 