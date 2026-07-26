add_library(Miscellaneous
    Coords.cc
)

target_include_directories(Miscellaneous PUBLIC
    ${CMAKE_SOURCE_DIR}/include/Exceptions
    ${CMAKE_SOURCE_DIR}/include/
)