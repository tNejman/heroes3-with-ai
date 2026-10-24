cmake_minimum_required(VERSION 3.25.0)
project(Heroes3App LANGUAGES CXX)
set(APP_NAME Heroes3App)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Build type is: ${CMAKE_BUILD_TYPE}")

option(CODE_COVERAGE "code coverage" ON)

# @TODO uncomment when clang-tidy is ready
# find_program(CLANG_TIDY_EXE NAMES clang-tidy) 
# set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" --use-color) #  --fix-errors

include(FetchContent)
include(CMakePrintHelpers)

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

set(DEPENDENCIES
    SFML
    json
    magic_enum
)

set(_prev_dev_err "${CMAKE_SUPPRESS_DEVELOPER_ERRORS}")
set(_prev_dev_warn "${CMAKE_SUPPRESS_DEVELOPER_WARNINGS}")
set(CMAKE_SUPPRESS_DEVELOPER_ERRORS ON CACHE BOOL "" FORCE)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE BOOL "" FORCE)

if (DEFINED CMAKE_CXX_CLANG_TIDY)
  set(_saved_clang_tidy "${CMAKE_CXX_CLANG_TIDY}")
  set(CMAKE_CXX_CLANG_TIDY "")
endif()
foreach(dependency ${DEPENDENCIES})
    message(STATUS "Fetching ${dependency} dependency")
    FetchContent_MakeAvailable(${dependency})
endforeach()
if (DEFINED CMAKE_CXX_CLANG_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "${_saved_clang_tidy}")
endif()

set(CMAKE_SUPPRESS_DEVELOPER_ERRORS "${_prev_dev_err}" CACHE BOOL "" FORCE)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS "${_prev_dev_warn}" CACHE BOOL "" FORCE)

set(TOOLS
  fetch_sprites.py
  fetch_fonts.py
)

option(FETCH_ASSETS "Download sprites at configure time" ON)
if(FETCH_ASSETS)
    find_package(Python3 REQUIRED COMPONENTS Interpreter) 
    foreach(tool ${TOOLS})
        message(STATUS "Fetching ${tool}")

        execute_process(
            COMMAND python3 ${CMAKE_SOURCE_DIR}/tools/${tool} ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE rc
        )

        if(NOT rc EQUAL 0)
            message(FATAL_ERROR "sprite fetch failed")
        endif()
    endforeach()
    
endif()

set(ENGINE_MODEL_MODULES
    IGame
    Coords
)

set(ENGINE_PLATFORM_MODULES
    Graphics
    Input
    LoadAndSaveTools
)

set(CORE_MODULES
    # Algorithms
    Artifact
    Battle
    Character
    Game
    Magic
    MapObject
    Player
    Resource
    Unit
    WorldMap
)

add_compile_options(-freflection -fdiagnostics-all-candidates)

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

foreach(module ${ENGINE_MODEL_MODULES})
    if(EXISTS ${CMAKE_SOURCE_DIR}/engine/model/src/engine/model/${module})
        add_subdirectory(${CMAKE_SOURCE_DIR}/engine/model/src/engine/model/${module})
    else()
        MESSAGE("skipping nonexistent dir: ./engine/model/src/engine/model/${module}")
    endif()

    target_include_directories(${module} PUBLIC
        ${CMAKE_SOURCE_DIR}/aux/include/
        ${CMAKE_SOURCE_DIR}/engine/model/include/
    )

    apply_compiler_flags(${module})
endforeach()

foreach(module ${CORE_MODULES})
    add_subdirectory(core/src/core/${module})
    target_include_directories(${module} PUBLIC
        ${CMAKE_SOURCE_DIR}/aux/include/ 
        ${CMAKE_SOURCE_DIR}/engine/model/include/
        ${CMAKE_SOURCE_DIR}/core/include/
      # ${CMAKE_SOURCE_DIR}/engine/model/include/ #### @TODO REMOVE ASAP
        
    )
    apply_compiler_flags(${module})
endforeach()

foreach(module ${ENGINE_PLATFORM_MODULES})
    if(EXISTS ${CMAKE_SOURCE_DIR}/engine/platform/src/engine/platform/${module})
        add_subdirectory(${CMAKE_SOURCE_DIR}/engine/platform/src/engine/platform/${module})
    else()
        MESSAGE("skipping nonexistent dir: ./engine/platform/src/engine/platform/${module}")
    endif()

    target_include_directories(${module} PUBLIC
        ${CMAKE_SOURCE_DIR}/aux/include/ 
        ${CMAKE_SOURCE_DIR}/engine/model/include/   
        ${CMAKE_SOURCE_DIR}/core/include/
        ${CMAKE_SOURCE_DIR}/engine/platform/include/
    )

    apply_compiler_flags(${module})
endforeach()

add_subdirectory(app)

enable_testing()
add_subdirectory(test)
