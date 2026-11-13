# gcov-based code coverage.
#
# Usage:
#   cmake --preset gcc-ninja-lld -DCODE_COVERAGE=ON
#   cmake --build build --target coverage
#
# The `coverage` target zeroes counters, runs ctest, then reports.
# With gcovr installed it writes an HTML report to build/coverage/index.html,
# otherwise it falls back to plain gcov and prints a per-file summary.

if(NOT CODE_COVERAGE)
  return()
endif()

find_program(GCOV_EXE NAMES gcov-16 gcov REQUIRED)
set(GCOV_COMMAND "${GCOV_EXE}")
message(STATUS "Code coverage enabled, using: ${GCOV_COMMAND}")

if(NOT GCOV_EXE)
  message(FATAL_ERROR "gcov not found but coverage enabled")
endif()

set(COVERAGE_DIR ${CMAKE_BINARY_DIR}/coverage)
file(MAKE_DIRECTORY ${COVERAGE_DIR})
find_program(GCOVR_EXE NAMES gcovr)

if(NOT GCOVR_EXE)
  message(FATAL_ERROR "gcovr not found but coverage enabled")
endif()

add_custom_target(coverage-clean
  COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
  COMMENT "Zeroing coverage counters"
  VERBATIM
)

add_custom_target(coverage
  COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR} --output-on-failure || true
  COMMAND ${GCOVR_EXE}
  --gcov-executable "${GCOV_COMMAND}"
  --root ${CMAKE_SOURCE_DIR}
  --object-directory ${CMAKE_BINARY_DIR}
  --filter ${CMAKE_SOURCE_DIR}/core/
  --filter ${CMAKE_SOURCE_DIR}/engine/
  --exclude ".*Exception\\.hpp$"
  --html-details ${COVERAGE_DIR}/index.html
  --print-summary
  DEPENDS coverage-clean
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Generating coverage report: ${COVERAGE_DIR}/index.html"
  VERBATIM
)
