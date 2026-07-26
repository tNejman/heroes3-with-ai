include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    SYSTEM
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

function(f_add_test_executable target_name file_name)
    add_executable(${target_name} ${file_name})
    target_link_libraries(${target_name} PRIVATE
        GTest::gtest_main
    )
    target_compile_options(${target_name} PRIVATE -O0 -g)
    gtest_discover_tests(${target_name})
endfunction()

set(TEST_DIRS
    ArtifactTest
    BattleTest
    CharacterTest
)

foreach(test_dir ${TEST_DIRS})
    add_subdirectory(${test_dir})
endforeach()