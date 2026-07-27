include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    SYSTEM
)

if(CLANG_TIDY_EXE)
    set(_saved_clang_tidy "${CMAKE_CXX_CLANG_TIDY}")
    set(CMAKE_CXX_CLANG_TIDY "")
    FetchContent_MakeAvailable(googletest)
    set(CMAKE_CXX_CLANG_TIDY "${_saved_clang_tidy}")
else()
    FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

function(f_add_test_executable target_name file_name)
    add_executable(${target_name} ${file_name})
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )
    target_link_libraries(${target_name} PRIVATE
        GTest::gtest_main
        SFML::Graphics
    )
    target_compile_options(${target_name} PRIVATE -O0 -g)
    gtest_discover_tests(${target_name})
endfunction()

set(TEST_DIRS
    ArtifactTest
    BattleTest
    CharacterTest
    UnitTest
    WorldMapTest
)

foreach(test_dir ${TEST_DIRS})
    add_subdirectory(${test_dir})
endforeach()