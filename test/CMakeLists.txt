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

function(f_add_test_executable target)
  cmake_parse_arguments(PARSE_ARGV 1 ARG "REFLECTION" "" "SOURCES;LIBRARIES")

  add_executable(${target} ${ARG_SOURCES})
  target_include_directories(${target} PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include/
    ${CMAKE_SOURCE_DIR}/aux/include/
    ${CMAKE_SOURCE_DIR}/engine/model/include/
  )
  target_link_libraries(${target} PRIVATE
    GTest::gtest_main
    ${ARG_LIBRARIES}
  )
  if(ARG_REFLECTION)
    target_compile_options(${target} PRIVATE -freflection)
  endif()

  # same warnings/sanitizers as production code
  apply_compiler_flags(${target})

  # discover at ctest time, not build time: a crashing test binary must not break the build
  gtest_discover_tests(${target} DISCOVERY_MODE PRE_TEST)
endfunction()

set(TEST_DIRS
  ArtifactTest
  BattleTest
  CharacterTest
  CoordsTest
  # GameTest
  UnitTest
  WorldMapTest
)

foreach(test_dir ${TEST_DIRS})
  add_subdirectory(${test_dir})
endforeach()
